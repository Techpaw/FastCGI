#pragma once

namespace Fcgi {
  enum class ProtocolStatusType {
    REQUEST_COMPLETE = 0,
    CANT_MPX_CONN = 1,
    OVERLOADED = 2,
    UNKNOWN_ROLE = 3
  };
}