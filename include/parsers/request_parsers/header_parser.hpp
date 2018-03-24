#pragma once

#include <header.hpp>
#include <calculators/bytes_reducer.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class HeaderParser {
      public:
        void parse(Header& header, char* str, std::uint8_t headerLength) {
          header.setVersion((std::uint8_t) str[0]);
          header.setType((Fcgi::HeaderType) str[1]);
          header.setRequestId(Calculators::BytesReducer::reduce16(str, 2));
          header.setContentLength(Calculators::BytesReducer::reduce16(str, 4));
          header.setPaddingLength((std::uint8_t) str[6]);
          header.setReserved((std::uint8_t) str[7]);
        }
      };
    }
  }
}