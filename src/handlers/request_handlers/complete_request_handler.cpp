#include <fastcgi/handlers/request_handlers/complete_request_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      void CompleteRequestHandler::handle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        auto builder = Builders::ResponseBuilder(connection, response);
        Application::instance().execute(connection, request, response);
        builder.stdout().build();
        builder.end().build(this->closeAfterWrite(request));
      }

      bool CompleteRequestHandler::mayHandle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        return request->getHeader().getType() == Constants::Header::ABORT_REQUEST ||
               this->lastPortionReceived(request);
      }

      bool CompleteRequestHandler::stopOnHandle() {
        return true;
      }

      bool CompleteRequestHandler::lastPortionReceived(const Pointers::RequestPointer& request) {
        return request->getHeader().getType() == Constants::Header::STDIN &&
               request->getHeader().getBodyLength() == 0;
      }
    }
  }
}