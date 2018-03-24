#pragma once

#include <map>

#include <request.hpp>
#include <header.hpp>
#include <body.hpp>
#include <state.hpp>
#include <exceptions/exceptions.hpp>
#include <handlers/request_handlers/header_handler.hpp>
#include <handlers/request_handlers/body_handler.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  class Connection;

  namespace Handlers {
    class ConnectionHandler {
    public:
      explicit ConnectionHandler();
      void setConnection(Pointers::ConnectionPointer& connection);
      void handleReadHead();
      void handleReadBody();
      RequestPointer getRequest();
      Pointers::ResponsePointer getResponse();
      State& getHeaderState();
      State& getBodyState();
    private:
      Pointers::ConnectionPointer connection;
      Pointers::ResponsePointer response;
      RequestHandlers::HeaderHandler headerHandler;
      RequestHandlers::BodyHandler bodyHandler;
      RequestPointer request;
      void checkLength(State&);
    };
  }
}