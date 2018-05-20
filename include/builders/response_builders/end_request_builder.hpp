#pragma once

#include <list>
#include <string>
#include <constants/header.hpp>
#include <constants/limits.hpp>
#include <constants/versions.hpp>
#include <calculators/bytes_expander.hpp>
#include <pointers/response_pointer.hpp>
#include <pointers/connection_pointer.hpp>
#include <builders/response_builders/base_builder.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      class EndRequestBuilder : private BaseBuilder {
      public:
        using BaseBuilder::BaseBuilder;
        void build(bool = false);
      private:
        void sendBody(bool = false);
      };
    }
  }
}