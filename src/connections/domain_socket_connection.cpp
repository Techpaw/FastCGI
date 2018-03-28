#include <boost/bind.hpp>
#include <connections/domain_socket_connection.hpp>

namespace Fcgi {
  namespace Connections {
    DomainSocketConnection::DomainSocketConnection(boost::asio::io_service& ioService) :
        socket(ioService), strand(ioService), connectionHandler{Handlers::ConnectionHandler(this)}
    {}

//    void DomainSocketConnection::setConnectionHandler(Pointers::ConnectionHandlerPointer& connectionHandler) {
//      this->connectionHandler = connectionHandler;
//    }

    stream_protocol::socket& DomainSocketConnection::getSocket() {
      return this->socket;
    }

    void DomainSocketConnection::start()  {
      this->headerState.allocateBuffer(Constants::Limits::HEADER_LENGTH);

      this->socket.async_read_some(
          boost::asio::buffer(this->headerState.getBuffer(), Constants::Limits::HEADER_LENGTH),
          this->strand.wrap(
              boost::bind(
                  &Connections::AbstractConnection::handleReadHead,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred
              )
          )
      );
    }

    void DomainSocketConnection::readBody(std::size_t bodyLength) {
      this->bodyState.allocateBuffer(bodyLength);

      this->socket.async_read_some(
          boost::asio::buffer(this->bodyState.getBuffer(), bodyLength),
          this->strand.wrap(
              boost::bind(
                  &Connections::AbstractConnection::handleReadBody,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred,
                  bodyLength
              )
          )
      );
    }

    void DomainSocketConnection::write(const char* data, std::size_t length, bool close) {
      this->socket.async_write_some(
          boost::asio::buffer(data, length),
          this->strand.wrap(
              boost::bind(&Connections::AbstractConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error, close)
          )
      );
    }

    void DomainSocketConnection::handleWrite(const boost::system::error_code& errorCode, bool close) {
      if (close) {
        boost::system::error_code ignored_ec;
        this->getSocket().shutdown(stream_protocol::socket::shutdown_both, ignored_ec);
      }
    }

    void DomainSocketConnection::handleReadHead(const boost::system::error_code& errorCode, unsigned char bytesTransferred) {
      std::string x = errorCode.message();
      this->headerState.setup(bytesTransferred, Constants::Limits::HEADER_LENGTH, errorCode);
      this->connectionHandler.handleReadHead();
    }

    void DomainSocketConnection::handleReadBody(const boost::system::error_code& errorCode, std::size_t bytesTransferred, std::size_t bodyLength) {
      this->bodyState.setup(bytesTransferred, bodyLength, errorCode);
      this->connectionHandler.handleReadBody();
    }

    State& DomainSocketConnection::getHeaderState() {
      return this->headerState;
    }

    State& DomainSocketConnection::getBodyState() {
      return this->bodyState;
    }
  }
}