#pragma once

#include <list>
#include <string>
#include <fastcgi/constants/header.hpp>
#include <fastcgi/constants/limits.hpp>
#include <fastcgi/constants/versions.hpp>
#include <fastcgi/calculators/bytes_expander.hpp>
#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/builders/response_builders/base_builder.hpp>

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