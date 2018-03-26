#pragma once

#include <state.hpp>
#include <request.hpp>
#include <header_type.hpp>
#include <parsers/request_parsers/body_parsing_chain.hpp>
#include <pointers/connection_pointer.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class BodyHandler {
      public:
        explicit BodyHandler();
        void handle(Pointers::ConnectionPointer& connection, RequestPointer& request);
      private:
        Pointers::ResponsePointer response;
        Parsers::RequestParsers::BodyParsingChain bodyParser{Parsers::RequestParsers::BodyParsingChain()};
        bool closeAfterWrite(RequestPointer&);
        bool lastPortionReceived(RequestPointer&);
        bool requestCompleted(RequestPointer&);
        bool paramsRequested(RequestPointer&);
        void handleInvalidRoleReceived(Pointers::ConnectionPointer&, RequestPointer&);
        void handleRequestCompleted(Pointers::ConnectionPointer&, RequestPointer&);
        void handleParamsRequested(Pointers::ConnectionPointer&, RequestPointer&);
        bool invalidRoleReceived(RequestPointer&);
      };
    }
  }
}