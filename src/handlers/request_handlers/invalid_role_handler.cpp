#include <fastcgi/handlers/request_handlers/invalid_role_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      void InvalidRoleHandler::handle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        auto rb = Builders::ResponseBuilder(connection, response);

        response->getHeader().setRequestId(request->getHeader().getRequestId());
        response->getHeader().setType(Constants::Header::STDOUT);
        response->setProtocolStatus(Constants::ProtocolStatus::UNKNOWN_ROLE);
        response->setAppStatus(Constants::ApplicationStatus::NOT_IMPLEMENTED);

        rb.end().build(this->closeAfterWrite(request));
      }

      bool InvalidRoleHandler::mayHandle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        auto role = (Constants::RoleType) Configuration::get<std::uint16_t>("APPLICATION_TYPE");
        return role != request->getBody().getRole();
      }

      bool InvalidRoleHandler::stopOnHandle() {
        return true;
      }
    }
  }
}