#pragma once

namespace Fcgi {
  enum class RoleType {
    RESPONDER = 1,
    AUTHORIZER = 2,
    FILTER = 3,
  };
}