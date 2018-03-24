#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <constants/limits.hpp>
#include <request.hpp>
#include <state.hpp>
#include <pointers/connection_handler_pointer.hpp>

namespace Fcgi {
  using boost::asio::local::stream_protocol;

  class Connection : public std::enable_shared_from_this<Connection> {
  public:
    explicit Connection(boost::asio::io_service& ioService);

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    void setConnectionHandler(Pointers::ConnectionHandlerPointer& connectionHandler);
    stream_protocol::socket& getSocket();
    void start();
    void readBody(std::size_t bodyLength) ;
    void handleReadHead(const boost::system::error_code& errorCode, unsigned char bytesTransferred);
    void handleReadBody(const boost::system::error_code& errorCode, std::size_t bytesTransferred, std::size_t bodyLength);
    void write(const char* data, std::size_t, bool = false);
    void handleWrite(const boost::system::error_code&, bool);
    State& getHeaderState();
    State& getBodyState();
  private:
    State headerState;
    State bodyState;
    Pointers::ConnectionHandlerPointer connectionHandler;
    stream_protocol::socket socket;
    stream_protocol::endpoint endpoint;
    boost::asio::io_service::strand strand;
  };
}