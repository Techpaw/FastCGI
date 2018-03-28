#pragma once

#include <list>
#include <string>
#include <header_type.hpp>
#include <buffer.hpp>
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
            Pointers::ConnectionPointer& connection,
            Pointers::ResponsePointer& response,
            TYPE type
        ) : BaseBuilder{connection, response},
            type{type}
        {}

        /**
         * Build and send STD* response
         * Automatically split the content by portions
         */
        void build() {
          Buffer& data = this->dataSource();

          while (!data.eof()) {
            this->sendPortion(data.readData(Constants::Limits::MAX_PORTION_LENGTH));
          }

          this->sendPortion("");
        }
      private:
        TYPE type;

        Buffer& dataSource() {
          if (this->type == TYPE::STDOUT) {
            return this->response->getBody().getBody();
          }

          return this->response->getBody().getError();
        }

        HeaderType headerType() {
          if (this->type == TYPE::STDOUT) {
            return HeaderType::STDOUT;
          }

          return HeaderType::STDERR;
        }

        /**
         * Send portion of STD* data
         * @param portion Portion content
         * @return void
         */
        void sendPortion(std::string portion) {
          this->sendHeader(this->headerType(), (std::uint16_t) portion.length());
          this->connection->write(portion.c_str(), (std::uint32_t) portion.length());
        }
      };
    }
  }
}