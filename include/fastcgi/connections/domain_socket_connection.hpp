#pragma once

#include <fastcgi/connections/abstract_connection.hpp>
#include <fastcgi/handlers/connection_handler.hpp>

namespace Fcgi {
  namespace Connections {
    class DomainSocketConnection : public AbstractConnection, public std::enable_shared_from_this<DomainSocketConnection> {
    public:
      using AbstractConnection::AbstractConnection;

      explicit DomainSocketConnection(boost::asio::io_service&);

      void start() override;
      void initConnectionHandler() override;
      void readBody(std::size_t bodyLength) override;

      void handleReadHead(
        const boost::system::error_code& errorCode,
        unsigned char bytesTransferred
      ) override;

      void handleReadBody(
        const boost::system::error_code& errorCode,
        std::size_t bytesTransferred,
        std::size_t bodyLength
      ) override;

      void write(
        const char* data, std::size_t,
        bool closeAfterWrite = false
      ) override;

      void handleWrite(
        const boost::system::error_code& errorCode,
        bool closeAfterWrite
      ) override;

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