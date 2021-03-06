#pragma once

namespace Fcgi {
  namespace Constants {
    enum class Header {
      BEGIN_REQUEST = 1,
      ABORT_REQUEST = 2,
      END_REQUEST = 3,
      PARAMS = 4,
      STDIN = 5,
      STDOUT = 6,
      STDERR = 7,
      DATA = 8,
      GET_VALUES = 9,
      GET_VALUES_RESULT = 10,
      UNKNOWN_TYPE = 11,
      MAXTYPE = 11
    };
  }
}