#pragma once

#include <map>

#include <fastcgi/state.hpp>
#include <fastcgi/exceptions/exceptions.hpp>
#include <fastcgi/handlers/request_handlers/header_handler.hpp>
#include <fastcgi/handlers/request_handlers/body_handlers_chain.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/pointers/request_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    class ConnectionHandler {
    public:
      explicit ConnectionHandler() = default;
      explicit ConnectionHandler(Pointers::ConnectionPointer);
      void handleReadHead();
      void handleReadBody();
    private:
      Pointers::ConnectionPointer connection;
      Pointers::ResponsePointer response;
      Pointers::RequestPointer request;
      RequestHandlers::HeaderHandler headerHandler;
      RequestHandlers::BodyHandlersChain bodyHandler;
    };
  }
}