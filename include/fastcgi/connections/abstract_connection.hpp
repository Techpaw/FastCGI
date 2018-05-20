#pragma once

#include <boost/asio.hpp>
#include <fastcgi/state.hpp>

namespace Fcgi {
  namespace Connections {
    using boost::asio::local::stream_protocol;

    class AbstractConnection {
    public:
      AbstractConnection(const AbstractConnection&) = delete;
      AbstractConnection& operator=(const AbstractConnection&) = delete;
      explicit AbstractConnection() = default;

      virtual void start() = 0;
      virtual stream_protocol::socket& getSocket() = 0;
      virtual void readBody(std::size_t bodyLength) = 0;

      virtual void handleReadHead(
        const boost::system::error_code& errorCode,
        unsigned char bytesTransferred
      ) = 0;

      virtual void handleReadBody(
        const boost::system::error_code& errorCode,
        std::size_t bytesTransferred,
        std::size_t bodyLength
      ) = 0;

      virtual void write(
        const char* data, std::size_t,
        bool closeAfterWrite = false
      ) = 0;

      virtual void handleWrite(
        const boost::system::error_code&,
        bool closeAfterWrite
      ) = 0;

      virtual void initConnectionHandler() = 0;
      virtual State& getHeaderState() = 0;
      virtual State& getBodyState() = 0;
    };
  }
}