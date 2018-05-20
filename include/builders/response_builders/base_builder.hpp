#pragma once

#include <constants/header.hpp>
#include <constants/limits.hpp>
#include <constants/versions.hpp>
#include <pointers/connection_pointer.hpp>
#include <pointers/response_pointer.hpp>
#include <calculators/bytes_expander.hpp>

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