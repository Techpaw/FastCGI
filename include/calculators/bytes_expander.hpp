#pragma once

#include <tuple>

namespace Fcgi {
  namespace Calculators {
    class BytesExpander {
    public:
      static std::tuple<std::uint8_t, std::uint8_t> expand16(std::uint16_t number) {
        return std::make_tuple(
          (std::uint8_t) (number & 0xFF),
          (std::uint8_t) ((number >> 8) & 0xFF)
        );
      }

      static std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t> expand32(std::uint32_t number) {
        return std::make_tuple(
          (std::uint8_t) ((number >> 24) & 0xFF),
          (std::uint8_t) ((number >> 16) & 0xFF),
          (std::uint8_t) ((number >> 8) & 0xFF),
          (std::uint8_t) (number & 0xFF)
        );
      }
    };
  }
}