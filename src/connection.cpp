#include <iostream>
#include <connection.hpp>

namespace Fcgi {
  using boost::asio::local::stream_protocol;

  Connection::Connection(boost::asio::io_service& ioService) :
    socket(ioService), strand(ioService)
  {}

  void Connection::setConnectionHandler(Pointers::ConnectionHandlerPointer& connectionHandler) {
    this->connectionHandler = connectionHandler;
  }

  stream_protocol::socket& Connection::getSocket() {
    return this->socket;
  }

  void Connection::start() {
    this->headerState.allocateBuffer(Constants::Limits::HEADER_LENGTH);

    this->socket.async_read_some(
        boost::asio::buffer(this->headerState.getBuffer(), Constants::Limits::HEADER_LENGTH),
        this->strand.wrap(
            boost::bind(
                &Connection::handleReadHead,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        )
    );
  }

  void Connection::readBody(std::size_t bodyLength) {
    this->bodyState.allocateBuffer(bodyLength);

    this->socket.async_read_some(
        boost::asio::buffer(this->bodyState.getBuffer(), bodyLength),
        this->strand.wrap(
            boost::bind(
                &Connection::handleReadBody,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred,
                bodyLength
            )
        )
    );
  }

  void Connection::write(const char* data, std::size_t length, bool close) {
    this->socket.async_write_some(
      boost::asio::buffer(data, length),
      this->strand.wrap(
        boost::bind(&Connection::handleWrite, shared_from_this(), boost::asio::placeholders::error, close)
      )
    );
  }

  void Connection::handleWrite(const boost::system::error_code& errorCode, bool close) {
    if (close) {
      boost::system::error_code ignored_ec;
      this->getSocket().shutdown(stream_protocol::socket::shutdown_both, ignored_ec);
    }
  }

  void Connection::handleReadHead(const boost::system::error_code& errorCode, unsigned char bytesTransferred) {
    this->headerState.setup(bytesTransferred, Constants::Limits::HEADER_LENGTH, errorCode);
    this->connectionHandler->handleReadHead();
  }

  void Connection::handleReadBody(const boost::system::error_code& errorCode, std::size_t bytesTransferred, std::size_t bodyLength) {
    this->bodyState.setup(bytesTransferred, bodyLength, errorCode);
    this->connectionHandler->handleReadBody();
  }

  State& Connection::getHeaderState() {
    return this->headerState;
  }

  State& Connection::getBodyState() {
    return this->bodyState;
  }
}