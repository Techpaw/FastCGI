#include <parsers/request_parsers/get_values_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      void GetValuesParser::parse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {}

      bool GetValuesParser::mayParse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        return request->getHeader().getType() == Constants::Header::GET_VALUES;
      }
    }
  }
}