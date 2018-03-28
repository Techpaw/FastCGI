#pragma once

#include <role_type.hpp>
#include <configuration.hpp>
#include <constants/flags.hpp>
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
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          auto rb = Builders::ResponseBuilder(connection, response);

          response->getHeader().setRequestId(request->getHeader().getRequestId());
          response->getHeader().setType(HeaderType::STDOUT);
          response->setprotocolStatus(ProtocolStatusType::UNKNOWN_ROLE);
          response->setAppStatus(501);

          rb.end().build(this->closeAfterWrite(request));
        }

        bool mayHandle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          auto role = (RoleType) Configuration::get<std::uint16_t>("APPLICATION_TYPE");
          return role != request->getBody().getRole();
        }
      };
    }
  }
}