#include <thread>
#include <boost/bind.hpp>

#include <server.hpp>
#include <connections/domain_socket_connection.hpp>

namespace Fcgi {
  Server::Server() : ioService{}, signals{ioService}, acceptor{ioService} {
    ::unlink("/tmp/my_socket.sock");

    this->signals.add(SIGINT);
    this->signals.add(SIGTERM);

    #if defined(SIGQUIT)
        this->signals.add(SIGQUIT);
    #endif

    this->signals.async_wait(std::bind(&Server::handleStop, this));

//      this->ioService = std::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());

    stream_protocol::endpoint endpoint("/tmp/my_socket.sock");

    this->acceptor.open(endpoint.protocol());
//    this->acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    this->acceptor.bind(endpoint);
    this->acceptor.listen();
//      stream_protocol::acceptor acceptor(this->ioService/*,*this->endpoint_ptr*/);
//      this->socket_ptr = std::shared_ptr<stream_protocol::socket>(new stream_protocol::socket(*this->ioService)); <-- connection level

    this->startAccept();
  }

  void Server::run()
  {
    std::vector<std::shared_ptr<std::thread>> threads;
    for (std::size_t i = 0; i < this->threadPoolSize; ++i) {
      std::shared_ptr<std::thread> thread(
          new std::thread(boost::bind(&boost::asio::io_service::run, &this->ioService))
      );

      threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i) {
      threads[i]->join();
    }
  }


  void Server::handleAccept(const boost::system::error_code& ec) {
    if (!ec) {
      this->connection->start();
    }

    this->startAccept();
  }

  void Server::startAccept()
  {
//    this->connectionHandler.reset(new Handlers::ConnectionHandler());

    this->connection = std::make_shared<Connections::DomainSocketConnection>(this->ioService);
    this->connection->initConnectionHandler();

//    this->connectionHandler->setConnection(this->connection);
//    this->connection->setConnectionHandler(this->connectionHandler);

    this->acceptor.async_accept(
        this->connection->getSocket(),
        boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error)
    );
  }

  void Server::handleStop() {
    this->ioService.stop();
  }
}