#pragma once

#include <pointers/connection_pointer.hpp>

namespace Fcgi {
  using boost::asio::local::stream_protocol;

  class Server {
  public:
    explicit Server(std::string connectionString = "");
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
  };
}