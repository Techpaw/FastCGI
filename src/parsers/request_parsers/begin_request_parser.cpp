#include <fastcgi/parsers/request_parsers/begin_request_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      void BeginRequestParser::parse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        request->getBody().setFlags((std::uint8_t) bodyState.getBuffer()[2]);

        request->getBody().setRole(
          (Constants::RoleType) Calculators::BytesReducer::reduce16(bodyState.getBuffer())
        );
      }

      bool BeginRequestParser::mayParse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        return request->getHeader().getType() == Constants::Header::BEGIN_REQUEST;
      }
    }
  }
}