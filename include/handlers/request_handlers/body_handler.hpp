#pragma once

#include <state.hpp>
#include <request.hpp>
#include <header_type.hpp>
#include <parsers/request_parsers/body_parsing_chain.hpp>
#include <pointers/connection_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class BodyHandler {
      public:
        explicit BodyHandler();
        void handle(Pointers::ConnectionPointer& connection, RequestPointer& request);
      private:
        Parsers::RequestParsers::BodyParsingChain bodyParser{Parsers::RequestParsers::BodyParsingChain()};
      };
    }
  }
}