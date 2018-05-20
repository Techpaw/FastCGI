#pragma once

#include <fastcgi/constants/header.hpp>
#include <fastcgi/constants/limits.hpp>
#include <fastcgi/constants/versions.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/calculators/bytes_expander.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      class BaseBuilder {
      public:
        explicit BaseBuilder() = default;

        explicit BaseBuilder(
          Pointers::ConnectionPointer&,
          Pointers::ResponsePointer&
        );

        void sendHeader(Constants::Header, std::uint16_t);
      protected:
        Pointers::ResponsePointer response;
        Pointers::ConnectionPointer connection;
      };
    }
  }
}