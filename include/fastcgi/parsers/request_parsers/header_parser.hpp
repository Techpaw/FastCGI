#pragma once

#include <fastcgi/header.hpp>
#include <fastcgi/calculators/bytes_reducer.hpp>

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