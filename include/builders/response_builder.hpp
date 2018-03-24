#pragma once

#include <list>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Builders {
    class ResponseBuilder {
    public:
      explicit ResponseBuilder() {

      }

      std::list<unsigned char*> toByteStreams(Pointers::ResponsePointer& response) {

      }

    private:
      std::list<unsigned char*> byteStreams;
    };
  }
}