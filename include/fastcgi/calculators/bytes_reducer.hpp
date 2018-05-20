#pragma once

#include <memory>

namespace Fcgi {
  namespace Calculators {
    class BytesReducer {
    public:
      static std::uint16_t reduce16(const char* str, std::size_t = 0);
      static std::uint32_t reduce32(const char* str, std::size_t = 0);
    };
  }
}