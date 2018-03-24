#pragma once

#include <handlers/connection_handler.hpp>

namespace Fcgi {
  namespace Pointers {
    typedef std::shared_ptr<Handlers::ConnectionHandler> ConnectionHandlerPointer;
  }
}