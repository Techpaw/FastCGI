#include <calculators/bytes_reducer.hpp>

namespace Fcgi {
  namespace Calculators {
    std::uint16_t BytesReducer::reduce16(const char* str, std::size_t startIndex) {
      return (((std::uint8_t) str[startIndex]) << 8) + ((std::uint8_t) str[startIndex + 1]);
    }

    std::uint32_t BytesReducer::reduce32(const char* str, std::size_t startIndex) {
      return ((((std::uint8_t) str[startIndex]) & 0x7f) << 24) +
             (((std::uint8_t) str[startIndex + 1]) << 16) +
             (((std::uint8_t) str[startIndex + 2]) << 8) +
             ((std::uint8_t) str[startIndex + 3]);
    }
  }
}