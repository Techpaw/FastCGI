#pragma once

#include <constants/header.hpp>
#include <builders/response_builder.hpp>
#include <handlers/request_handlers/abstract_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class GetValuesHandler : public AbstractHandler {
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