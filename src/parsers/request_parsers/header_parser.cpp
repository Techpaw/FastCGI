#include <fastcgi/parsers/request_parsers/header_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      void HeaderParser::parse(Header& header, char* str, std::uint8_t headerLength) {
        header.setVersion((std::uint8_t) str[0]);
        header.setType((Fcgi::Constants::Header) str[1]);
        header.setRequestId(Calculators::BytesReducer::reduce16(str, 2));
        header.setContentLength(Calculators::BytesReducer::reduce16(str, 4));
        header.setPaddingLength((std::uint8_t) str[6]);
        header.setReserved((std::uint8_t) str[7]);
      }
    }
  }
}