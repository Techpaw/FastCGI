#include <handlers/request_handlers/header_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      void HeaderHandler::handle(
          const Pointers::ConnectionPointer& connection,
          const Pointers::RequestPointer& request,
          const Pointers::ResponsePointer& response
      ) {
        Parsers::RequestParsers::HeaderParser().parse(
          request->getHeader(),
          this->headerState(connection).getBuffer(),
          (std::uint8_t) this->headerState(connection).getBytesTransferred()
        );
      };

      bool HeaderHandler::mayHandle(
          const Pointers::ConnectionPointer& connection,
          const Pointers::RequestPointer& request,
          const Pointers::ResponsePointer& response
      ) {
        return true;
      };

      State& HeaderHandler::headerState(const Pointers::ConnectionPointer& connection) {
        return connection->getHeaderState();
      }
    }
  }
}