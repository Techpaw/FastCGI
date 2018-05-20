#include <thread>
#include <boost/bind.hpp>

#include <server.hpp>
#include <connections/domain_socket_connection.hpp>

namespace Fcgi {
  Server::Server(std::string connectionString) :
    ioService{},
    signals{ioService},
    acceptor{ioService}
  {
    ::unlink(connectionString.c_str());

    this->signals.add(SIGINT);
    this->signals.add(SIGTERM);

    #if defined(SIGQUIT)
        this->signals.add(SIGQUIT);
    #endif

    this->signals.async_wait(std::bind(&Server::handleStop, this));
    stream_protocol::endpoint endpoint(connectionString);

    this->acceptor.open(endpoint.protocol());
    this->acceptor.bind(endpoint);
    this->acceptor.listen();

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
    this->connection = std::make_shared<Connections::DomainSocketConnection>(this->ioService);
    this->connection->initConnectionHandler();

    this->acceptor.async_accept(
        this->connection->getSocket(),
        boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error)
    );
  }

  void Server::handleStop() {
    this->ioService.stop();
  }
}