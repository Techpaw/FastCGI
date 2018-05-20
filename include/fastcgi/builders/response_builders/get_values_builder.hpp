#pragma once

#include <map>
#include <list>
#include <string>
#include <fastcgi/buffer.hpp>
#include <fastcgi/configuration.hpp>
#include <fastcgi/constants/header.hpp>
#include <fastcgi/constants/versions.hpp>
#include <fastcgi/constants/limits.hpp>
#include <fastcgi/calculators/bytes_expander.hpp>
#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/builders/response_builders/base_builder.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      class GetValuesBuilder : private BaseBuilder {
      public:
        using BaseBuilder::BaseBuilder;
        void build();
      private:
        void appendDefaultValues();
        void appendLengthInfo(const std::string&, std::string&);
      };
    }
  }
}