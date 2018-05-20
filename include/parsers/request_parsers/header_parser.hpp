#pragma once

#include <header.hpp>
#include <calculators/bytes_reducer.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class HeaderParser {
      public:
        void parse(Header& header, char*, std::uint8_t);
      };
    }
  }
}