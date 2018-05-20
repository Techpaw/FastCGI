#include <handlers/connection_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    ConnectionHandler::ConnectionHandler(Pointers::ConnectionPointer connection) :
      request{std::make_shared<Request>()},
      response(std::make_shared<Response>()),
      connection{connection},
      bodyHandler{RequestHandlers::BodyHandlersChain()},
      headerHandler{RequestHandlers::HeaderHandler()}
    {}

    void ConnectionHandler::handleReadHead() {
      headerHandler.handle(this->connection, this->request, this->response);
      this->connection->readBody(this->request->getHeader().getBodyLength());
    }

    void ConnectionHandler::handleReadBody() {
      bodyHandler.handle(this->connection, this->request, this->response);
    }
  }
}