#pragma once

#include <list>
#include <string>
#include <buffer.hpp>
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
      class OutBuilder : private BaseBuilder {
      public:
        enum TYPE { STDOUT = 0, STDERR };

        using BaseBuilder::BaseBuilder;

        /**
         * Construct a new StdoutBuilder
         * @param connection
         * @param response
         */
        explicit OutBuilder(
          Pointers::ConnectionPointer&,
          Pointers::ResponsePointer&,
          TYPE type
        );

        /**
         * Build and send STD* response
         * Automatically split the content by portions
         */
        void build();
      private:
        TYPE type;

        Buffer& dataSource();
        Constants::Header headerType();

        /**
         * Send portion of STD* data
         * @param portion Portion content
         * @return void
         */
        void sendPortion(std::string);
      };
    }
  }
}