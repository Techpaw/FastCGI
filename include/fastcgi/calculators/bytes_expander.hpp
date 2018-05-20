#pragma once

#include <tuple>

namespace Fcgi {
  namespace Calculators {
    class BytesExpander {
    public:
      static std::tuple<std::uint8_t, std::uint8_t>
      expand16(std::uint16_t);

      static std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>
      expand32(std::uint32_t);
    };
  }
}