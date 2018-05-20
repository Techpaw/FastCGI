#include <fastcgi/handlers/request_handlers/fallback_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      void FallbackHandler::handle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        connection->start();
      }

      bool FallbackHandler::mayHandle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        return true;
      }
    }
  }
}