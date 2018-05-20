#include <handlers/request_handlers/body_parser_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      void BodyParserHandler::handle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        Parsers::RequestParsers::BodyParsingChain()
            .parse(request, connection->getBodyState(), connection->getHeaderState()
        );
      }

      bool BodyParserHandler::mayHandle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        return true;
      }
    }
  }
}