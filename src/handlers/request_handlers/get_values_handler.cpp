#include <handlers/request_handlers/get_values_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      void GetValuesHandler::handle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        auto rb = Builders::ResponseBuilder(connection, response);
        rb.values().build();
      }

      bool GetValuesHandler::mayHandle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        return request->getHeader().getType() == Constants::Header::GET_VALUES;
      }
    }
  }
}