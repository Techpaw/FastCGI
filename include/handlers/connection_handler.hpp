#pragma once

#include <map>

#include <state.hpp>
#include <exceptions/exceptions.hpp>
#include <handlers/request_handlers/header_handler.hpp>
#include <handlers/request_handlers/body_handlers_chain.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    class ConnectionHandler {
    public:
      explicit ConnectionHandler() = default;
      explicit ConnectionHandler(Connections::AbstractConnection* connection);
//      void setConnection(Pointers::ConnectionPointer& connection);
      void handleReadHead();
      void handleReadBody();
    private:
      Pointers::ConnectionPointer connection;
      Pointers::ResponsePointer response;
      RequestHandlers::HeaderHandler headerHandler;
      RequestHandlers::BodyHandlersChain bodyHandler;
      RequestPointer request;
      void checkLength(State&);
    };
  }
}