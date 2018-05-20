#pragma once

#include <configuration.hpp>
#include <constants/flags.hpp>
#include <constants/role_type.hpp>
#include <calculators/bytes_reducer.hpp>
#include <builders/response_builder.hpp>
#include <handlers/request_handlers/abstract_handler.hpp>

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