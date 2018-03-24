#pragma once

#include <list>
#include <string>
#include <header_type.hpp>
#include <constants/limits.hpp>
#include <constants/versions.hpp>
#include <calculators/bytes_expander.hpp>
#include <pointers/response_pointer.hpp>
#include <pointers/connection_pointer.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      class EndRequestBuilder {
      public:
        explicit EndRequestBuilder(Pointers::ConnectionPointer& connection, Pointers::ResponsePointer& response) :
            connection{connection}, response{response}
        {}

        void build() {
          this->sendHeader();
          this->sendBody();
        }
      private:
        Pointers::ResponsePointer response;
        Pointers::ConnectionPointer connection;

        void sendHeader() {
          char* buffer = new char[Constants::Limits::HEADER_LENGTH];
          auto contentLength = Calculators::BytesExpander::expand16(Constants::Limits::END_REQUEST_BODY_LENGTH);
          auto requestId = Calculators::BytesExpander::expand16(
              this->response->getHeader().getRequestId()
          );

          buffer[0] = Constants::Versions::FCGI_VERSION;
          buffer[1] = (std::uint8_t) HeaderType::END_REQUEST;
          buffer[2] = std::get<1>(requestId);
          buffer[3] = std::get<0>(requestId);
          buffer[4] = std::get<1>(contentLength);
          buffer[5] = std::get<0>(contentLength);
          buffer[6] = '\0';
          buffer[7] = '\0';

          this->connection->write(buffer, Constants::Limits::HEADER_LENGTH);
          delete[] buffer;
        }

        void sendBody() {
          char* buffer = new char[Constants::Limits::HEADER_LENGTH];
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

          this->connection->write(buffer, Constants::Limits::HEADER_LENGTH, true);
          delete[] buffer;
        }
      };
    }
  }
}