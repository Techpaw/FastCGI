#pragma once

namespace Fcgi {
  namespace Calculators {
    class BytesReducer {
    public:
      static std::uint16_t reduce16(const char* str, std::size_t startIndex = 0) {
        return (((std::uint8_t) str[startIndex]) << 8) + ((std::uint8_t) str[startIndex + 1]);
      }

      static std::uint32_t reduce32(const char* str, std::size_t startIndex = 0) {
        return ((((std::uint8_t) str[startIndex]) & 0x7f) << 24) +
               (((std::uint8_t) str[startIndex + 1]) << 16) +
               (((std::uint8_t) str[startIndex + 2]) << 8) +
               ((std::uint8_t) str[startIndex + 3]);
      }
    };
  }
}