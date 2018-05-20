#include <fastcgi/parsers/request_parsers/stdin_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      void StdinParser::parse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        request->getBody().appendBody(bodyState.getBuffer(), bodyState.getBytesReceived());
      }

      bool StdinParser::mayParse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        return request->getHeader().getType() == Constants::Header::STDIN;
      }
    }
  }
}