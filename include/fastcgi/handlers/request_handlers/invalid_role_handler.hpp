#pragma once

#include <fastcgi/configuration.hpp>
#include <fastcgi/constants/flags.hpp>
#include <fastcgi/constants/role_type.hpp>
#include <fastcgi/calculators/bytes_reducer.hpp>
#include <fastcgi/builders/response_builder.hpp>
#include <fastcgi/handlers/request_handlers/abstract_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class InvalidRoleHandler : public AbstractHandler {
      public:
        void handle(
          const Pointers::ConnectionPointer& connection,
          const Pointers::RequestPointer& request,
          const Pointers::ResponsePointer& response
        ) override ;

        bool mayHandle(
          const Pointers::ConnectionPointer& connection,
          const Pointers::RequestPointer& request,
          const Pointers::ResponsePointer& response
        ) override ;

        bool stopOnHandle() override;
      };
    }
  }
}