#include <connection.hpp>
#include <response.hpp>
#include <handlers/connection_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    ConnectionHandler::ConnectionHandler() :
      request{new Request()}, response(new Response())
    {}

    void ConnectionHandler::setConnection(Pointers::ConnectionPointer& connection) {
      this->connection = connection;
    };

    void ConnectionHandler::handleReadHead() {
//        this->checkLength(this->connection->getHeaderState());
      headerHandler.handle(this->connection, this->request);
      this->connection->readBody(this->request->getHeader().getBodyLength());
    }

    void ConnectionHandler::handleReadBody() {
//        this->checkLength(this->connection->getBodyState());
      bodyHandler.handle(this->connection, this->request);
    }

    RequestPointer ConnectionHandler::getRequest() {
      return this->request;
    }

    Pointers::ResponsePointer ConnectionHandler::getResponse() {
      return this->response;
    }

    State& ConnectionHandler::getHeaderState() {
      return this->connection->getHeaderState();
    }

    State& ConnectionHandler::getBodyState() {
      return this->connection->getHeaderState();
    }

    void ConnectionHandler::checkLength(State& state) {
      if (state.getBytesTransferred() != state.getBytesReceived() || (bool) state.getErrorCode()) {
        raise(Exceptions::InvalidLengthException("Unexpected content length received"));
      }
    }
  }
}