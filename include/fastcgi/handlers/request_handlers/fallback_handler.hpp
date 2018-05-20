#pragma once

#include <fastcgi/handlers/request_handlers/abstract_handler.hpp>
#include <fastcgi/parsers/request_parsers/body_parsing_chain.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class FallbackHandler : public AbstractHandler {
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