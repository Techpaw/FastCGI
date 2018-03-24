#include <connection.hpp>
#include <handlers/request_handlers/header_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      HeaderHandler::HeaderHandler() {
        this->headerParser = Parsers::RequestParsers::HeaderParser();
      }

      void HeaderHandler::handle(Pointers::ConnectionPointer connection, RequestPointer request) {
        headerParser.parse(
            request->getHeader(),
            this->headerState(connection).getBuffer(),
            (std::uint8_t) this->headerState(connection).getBytesTransferred()
        );
      };

      State& HeaderHandler::headerState(const Pointers::ConnectionPointer& connection) {
        return connection->getHeaderState();
      }
    }
  }
}