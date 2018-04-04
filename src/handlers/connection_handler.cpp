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
//      this->checkLength(this->connection->getHeaderState());
      headerHandler.handle(this->connection, this->request, this->response);
      this->connection->readBody(this->request->getHeader().getBodyLength());
    }

    void ConnectionHandler::handleReadBody() {
//      this->checkLength(this->connection->getBodyState());
      bodyHandler.handle(this->connection, this->request, this->response);
    }

//    void ConnectionHandler::checkLength(State& state) {
//      if (state.getBytesTransferred() != state.getBytesReceived() || (bool) state.getErrorCode()) {
//        raise_exception(Exceptions::InvalidLengthException("Unexpected content length received"));
//      }
//    }
  }
}