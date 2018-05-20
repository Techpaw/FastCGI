#pragma once

#include <handlers/request_handlers/abstract_handler.hpp>
#include <parsers/request_parsers/body_parsing_chain.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class BodyParserHandler : public AbstractHandler {
      public:
        void handle(
            const Pointers::ConnectionPointer& connection,
            const Pointers::RequestPointer& request,
            const Pointers::ResponsePointer& response
        ) override;

        bool mayHandle(
            const Pointers::ConnectionPointer& connection,
            const Pointers::RequestPointer& request,
            const Pointers::ResponsePointer& response
        ) override;
      };
    }
  }
}