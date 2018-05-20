#include <fastcgi/calculators/bytes_expander.hpp>

namespace Fcgi {
  namespace Calculators {
    std::tuple<std::uint8_t, std::uint8_t>
    BytesExpander::expand16(std::uint16_t number) {
      return std::make_tuple(
          (std::uint8_t) (number & 0xFF),
          (std::uint8_t) ((number >> 8) & 0xFF)
      );
    }

    std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>
    BytesExpander::expand32(std::uint32_t number) {
      return std::make_tuple(
          (std::uint8_t) ((number >> 24) & 0xFF),
          (std::uint8_t) ((number >> 16) & 0xFF),
          (std::uint8_t) ((number >> 8) & 0xFF),
          (std::uint8_t) (number & 0xFF)
      );
    }
  }
}