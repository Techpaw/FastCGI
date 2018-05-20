#pragma once

#include <fastcgi/state.hpp>
#include <fastcgi/request.hpp>
#include <fastcgi/handlers/request_handlers/abstract_handler.hpp>
#include <fastcgi/parsers/request_parsers/header_parser.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class HeaderHandler : public AbstractHandler {
      public:
        explicit HeaderHandler() = default;

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
      private:
        State& headerState(const Pointers::ConnectionPointer&);
      };
    }
  }
}