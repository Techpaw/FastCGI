#include <parsers/request_parsers/data_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      void DataParser::parse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        request->getBody().appendData(bodyState.getBuffer(), bodyState.getBytesReceived());
      }

      bool DataParser::mayParse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        return request->getHeader().getType() == Constants::Header::DATA;
      }
    }
  }
}