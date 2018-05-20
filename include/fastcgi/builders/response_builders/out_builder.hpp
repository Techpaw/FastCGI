#pragma once

#include <list>
#include <string>
#include <fastcgi/buffer.hpp>
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