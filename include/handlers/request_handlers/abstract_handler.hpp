#pragma once

#include <constants/flags.hpp>
#include <pointers/connection_pointer.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class AbstractHandler {
      public:
        virtual void handle(const Pointers::ConnectionPointer&, const RequestPointer&, Pointers::ResponsePointer&) = 0;
        virtual bool mayHandle(const Pointers::ConnectionPointer&, const RequestPointer&, Pointers::ResponsePointer&) = 0;
        virtual ~AbstractHandler() = default;
      protected:
        bool closeAfterWrite(const RequestPointer& request) {
          return (request->getBody().getFlags() & Constants::Flags::KEEP_CONN) == 0;
        }
      };
    }
  }
}