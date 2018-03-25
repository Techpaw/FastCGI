#pragma once

#include <list>
#include <string>
#include <header_type.hpp>
#include <connection.hpp>
#include <buffer.hpp>
#include <constants/versions.hpp>
#include <constants/limits.hpp>
#include <calculators/bytes_expander.hpp>
#include <pointers/response_pointer.hpp>
#include <pointers/connection_pointer.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      class OutBuilder {
      public:
        enum TYPE { STDOUT = 0, STDERR };

        /**
         * Construct a new StdoutBuilder
         * @param connection
         * @param response
         */
        explicit OutBuilder(
            Pointers::ConnectionPointer& connection,
            Pointers::ResponsePointer& response,
            TYPE type
        ) : connection{connection},
            response{response},
            type{type}
        {}

        /**
         * Build and send STDOUT response
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
        Pointers::ResponsePointer response;
        Pointers::ConnectionPointer connection;
        TYPE type;

        Buffer& dataSource() {
          if (this->type == TYPE::STDOUT) {
            return this->response->getBody().getBody();
          }

          return this->response->getBody().getError();
        }

        HeaderType sourceType() {
          if (this->type == TYPE::STDOUT) {
            return HeaderType::STDOUT;
          }

          return HeaderType::STDERR;
        }

        /**
         * Send portion of STDOUT data
         * @param portion Portion content
         * @return void
         */
        void sendPortion(std::string portion) {
          char buffer[Constants::Limits::HEADER_LENGTH];
          std::uint32_t portionLength = portion.length();
          auto contentLength = Calculators::BytesExpander::expand16((std::uint16_t) portion.length());
          auto requestId = Calculators::BytesExpander::expand16(
            this->response->getHeader().getRequestId()
          );

          buffer[0] = Constants::Versions::FCGI_VERSION;
          buffer[1] = (std::uint8_t) this->sourceType();
          buffer[2] = std::get<1>(requestId);
          buffer[3] = std::get<0>(requestId);
          buffer[4] = std::get<1>(contentLength);
          buffer[5] = std::get<0>(contentLength);
          buffer[6] = '\0';
          buffer[7] = '\0';

          this->connection->write(buffer, Constants::Limits::HEADER_LENGTH);
          this->connection->write(portion.c_str(), portionLength);
        }
      };
    }
  }
}