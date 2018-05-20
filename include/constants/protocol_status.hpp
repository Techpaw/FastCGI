#pragma once

namespace Fcgi {
  namespace Constants {
    enum class ProtocolStatus {
      REQUEST_COMPLETE = 0,
      CANT_MPX_CONN = 1,
      OVERLOADED = 2,
      UNKNOWN_ROLE = 3
    };
  }
}