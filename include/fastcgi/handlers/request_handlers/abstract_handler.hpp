#pragma once

#include <fastcgi/constants/flags.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/pointers/request_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class AbstractHandler {
      public:
        virtual void handle(
          const Pointers::ConnectionPointer&,
          const Pointers::RequestPointer&,
          const Pointers::ResponsePointer&
        ) = 0;

        virtual bool mayHandle(
          const Pointers::ConnectionPointer&,
          const Pointers::RequestPointer&,
          const Pointers::ResponsePointer&
        ) = 0;

        virtual ~AbstractHandler() = default;

        virtual bool stopOnHandle() {
          return false;
        }
      protected:
        virtual bool closeAfterWrite(const Pointers::RequestPointer& request) {
          return (request->getBody().getFlags() & Constants::Flags::KEEP_CONN) == 0;
        }
      };
    }
  }
}