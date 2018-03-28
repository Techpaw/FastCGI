#pragma once

#include <header_type.hpp>
#include <builders/response_builder.hpp>
#include <handlers/request_handlers/abstract_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class GetValuesHandler : public AbstractHandler {
      public:
        void handle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          auto rb = Builders::ResponseBuilder(connection, response);
          rb.values().build();
        }

        bool mayHandle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          return request->getHeader().getType() == HeaderType::GET_VALUES;
        }
      };
    }
  }
}