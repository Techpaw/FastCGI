#pragma once

#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/handlers/request_handlers/abstract_handler.hpp>
#include <fastcgi/handlers/request_handlers/body_parser_handler.hpp>
#include <fastcgi/handlers/request_handlers/invalid_role_handler.hpp>
#include <fastcgi/handlers/request_handlers/get_values_handler.hpp>
#include <fastcgi/handlers/request_handlers/complete_request_handler.hpp>
#include <fastcgi/handlers/request_handlers/fallback_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class BodyHandlersChain : public AbstractHandler {
      public:
        explicit BodyHandlersChain();

        void add(std::unique_ptr<AbstractHandler> handler);

        void handle(
          const Pointers::ConnectionPointer&,
          const Pointers::RequestPointer&,
          const Pointers::ResponsePointer&
        ) override;

        bool mayHandle(
          const Pointers::ConnectionPointer&,
          const Pointers::RequestPointer&,
          const Pointers::ResponsePointer&
        ) override;
      private:
        std::list<std::unique_ptr<AbstractHandler>> handlersList;
      };
    };
  }
}