#pragma once

//#include <boost/bind.hpp>
//#include <boost/asio.hpp>
//
//#include <constants/limits.hpp>
//#include <state.hpp>
//#include <pointers/connection_handler_pointer.hpp>

#include <connections/abstract_connection.hpp>
#include <handlers/connection_handler.hpp>

namespace Fcgi {
  namespace Connections {
    class DomainSocketConnection : public AbstractConnection, public std::enable_shared_from_this<DomainSocketConnection> {
    public:
      using AbstractConnection::AbstractConnection;

      explicit DomainSocketConnection(boost::asio::io_service&);

      void start() override;
      void initConnectionHandler() override;
      void readBody(std::size_t bodyLength) override;
      void handleReadHead(const boost::system::error_code& errorCode, unsigned char bytesTransferred) override;
      void handleReadBody(const boost::system::error_code& errorCode, std::size_t bytesTransferred, std::size_t bodyLength) override;
      void write(const char* data, std::size_t, bool close = false) override;
      void handleWrite(const boost::system::error_code&, bool) override;
      stream_protocol::socket& getSocket() override;
      State& getHeaderState() override;
      State& getBodyState() override;
    private:
      State headerState;
      State bodyState;
      Handlers::ConnectionHandler connectionHandler;
      stream_protocol::socket socket;
      stream_protocol::endpoint endpoint;
      boost::asio::io_service::strand strand;
    };
  }
}