#pragma once

#include <thread>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <pointers/connection_pointer.hpp>
#include <pointers/connection_handler_pointer.hpp>

namespace Fcgi {
  using boost::asio::local::stream_protocol;

  class Server {
  public:
    explicit Server();
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void run();
    void handleAccept(const boost::system::error_code&);
    void startAccept();
    void handleStop();
  private:
    boost::asio::io_service ioService;
    stream_protocol::acceptor acceptor;
    boost::asio::signal_set signals;
    uint8_t threadPoolSize = 16;
    Pointers::ConnectionPointer connection;
    Pointers::ConnectionHandlerPointer connectionHandler;
  };
}