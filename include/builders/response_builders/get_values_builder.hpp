#pragma once

#include <map>
#include <list>
#include <string>
#include <buffer.hpp>
#include <configuration.hpp>
#include <constants/header.hpp>
#include <constants/versions.hpp>
#include <constants/limits.hpp>
#include <calculators/bytes_expander.hpp>
#include <pointers/response_pointer.hpp>
#include <pointers/connection_pointer.hpp>
#include <builders/response_builders/base_builder.hpp>

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