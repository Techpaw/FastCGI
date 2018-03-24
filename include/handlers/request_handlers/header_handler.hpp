#pragma once

#include <state.hpp>
#include <request.hpp>
#include <parsers/request_parsers/header_parser.hpp>
#include <pointers/connection_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class HeaderHandler {
      public:
        explicit HeaderHandler();
        void handle(Pointers::ConnectionPointer, RequestPointer);
      private:
        Parsers::RequestParsers::HeaderParser headerParser;
        State& headerState(const Pointers::ConnectionPointer&);
      };
    }
  }
}