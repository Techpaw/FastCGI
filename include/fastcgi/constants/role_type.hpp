#pragma once

namespace Fcgi {
  namespace Constants {
    enum class RoleType {
      RESPONDER = 1,
      AUTHORIZER = 2,
      FILTER = 3,
    };
  }
}