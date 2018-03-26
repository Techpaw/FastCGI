#pragma once

#include <list>
#include <string>
#include <header_type.hpp>
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

        void build(bool closeAfterWrite = false) {
          this->sendHeader(HeaderType::END_REQUEST, Constants::Limits::END_REQUEST_BODY_LENGTH);
          this->sendBody(closeAfterWrite);
        }

      private:
        void sendBody(bool closeAfterWrite = false) {
          char buffer[Constants::Limits::END_REQUEST_BODY_LENGTH];
          auto appStatus = Calculators::BytesExpander::expand32(this->response->getAppStatus());
          auto requestId = Calculators::BytesExpander::expand16(
              this->response->getHeader().getRequestId()
          );

          buffer[0] = std::get<3>(appStatus);
          buffer[1] = std::get<2>(appStatus);
          buffer[2] = std::get<1>(appStatus);
          buffer[3] = std::get<0>(appStatus);
          buffer[4] = (std::uint8_t) this->response->getProtocolStatus();
          buffer[5] = '\0';
          buffer[6] = '\0';
          buffer[7] = '\0';

          this->connection->write(buffer, Constants::Limits::HEADER_LENGTH, closeAfterWrite);
        }
      };
    }
  }
}