#pragma once

#include <memory>

namespace Fcgi {
  namespace Constants {
    namespace Limits {
      const unsigned char MIN_PARAMS_LENGTH = 2;
      const unsigned char HEADER_LENGTH = 8;
      const unsigned char BEGIN_REQUEST_BODY_LENGTH = 8;
      const unsigned char END_REQUEST_BODY_LENGTH = 8;
      const std::uint16_t MAX_PORTION_LENGTH = 65535;
      const std::uint32_t MAX_IN_MEMORY_BUFFER_SIZE = 2097152;
      const std::uint16_t MAX_IN_MEMORY_BUFFER_STEP = 2048;
    }
  }
}