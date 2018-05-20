#pragma once

#include <fastcgi/response.hpp>

namespace Fcgi {
  namespace Pointers {
    typedef std::shared_ptr<Response> ResponsePointer;
  }
}