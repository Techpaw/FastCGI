#pragma once

#include <fastcgi/request.hpp>

namespace Fcgi {
  namespace Pointers {
    typedef std::shared_ptr<Request> RequestPointer;
  }
}