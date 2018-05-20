#pragma once

#include <fastcgi/connections/abstract_connection.hpp>

namespace Fcgi {
  namespace Pointers {
    typedef std::shared_ptr<Connections::AbstractConnection> ConnectionPointer;
  }
}