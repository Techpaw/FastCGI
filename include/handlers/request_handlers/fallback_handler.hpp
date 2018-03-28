#pragma once

#include <handlers/request_handlers/abstract_handler.hpp>
#include <parsers/request_parsers/body_parsing_chain.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class FallbackHandler : public AbstractHandler {
      public:
        void handle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          Parsers::RequestParsers::BodyParsingChain().parse(request,
            connection->getBodyState(),
            connection->getHeaderState()
          );

          connection->start();
        }

        bool mayHandle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          return true;
        }
      };
    }
  }
}