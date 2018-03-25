#pragma once

#include <map>
#include <list>
#include <string>
#include <header_type.hpp>
#include <connection.hpp>
#include <buffer.hpp>
#include <configuration.hpp>
#include <constants/versions.hpp>
#include <constants/limits.hpp>
#include <calculators/bytes_expander.hpp>
#include <pointers/response_pointer.hpp>
#include <pointers/connection_pointer.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      class GetValuesBuilder {
      public:
        explicit GetValuesBuilder(
            Pointers::ConnectionPointer& connection,
            Pointers::ResponsePointer& response
        ) : connection{connection},
            response{response}
        {}

        void build() {
          std::string output;

          this->appendDefaultValues();

          for (auto const& pair : this->response->getBody().getParams()) {
            this->appendLengthInfo(pair.first, output);
            this->appendLengthInfo(pair.second, output);
            output.append(pair.first);
            output.append(pair.second);
          }

          this->sendData(output);
        }

      private:
        Pointers::ResponsePointer response;
        Pointers::ConnectionPointer connection;

        void appendDefaultValues() {
          this->response->getBody().setParam("FCGI_MAX_CONNS", Configuration::get<std::string>("FCGI_MAX_CONNS"));
          this->response->getBody().setParam("FCGI_MAX_REQS", Configuration::get<std::string>("FCGI_MAX_REQS"));
          this->response->getBody().setParam("FCGI_MPXS_CONNS", Configuration::get<std::string>("FCGI_MPXS_CONNS"));
        }

        void appendLengthInfo(const std::string& source, std::string& destination) {
          if (source.length() > 255) {
            auto nameLength = Calculators::BytesExpander::expand32((std::uint32_t) source.length());
            char buffer[4];

            buffer[0] = std::get<3>(nameLength);
            buffer[1] = std::get<2>(nameLength);
            buffer[2] = std::get<1>(nameLength);
            buffer[3] = std::get<0>(nameLength);

            destination.append(buffer);
          } else {
            char buffer[1];
            buffer[0] = (std::uint8_t) source.length();
            destination.append(buffer);
          }
        }

        void sendData(std::string& data) {
          char buffer[Constants::Limits::HEADER_LENGTH];
          auto contentLength = Calculators::BytesExpander::expand16((std::uint16_t) data.length());
          auto requestId = Calculators::BytesExpander::expand16(
            this->response->getHeader().getRequestId()
          );

          buffer[0] = Constants::Versions::FCGI_VERSION;
          buffer[1] = (std::uint8_t) HeaderType::GET_VALUES_RESULT;
          buffer[2] = std::get<1>(requestId);
          buffer[3] = std::get<0>(requestId);
          buffer[4] = std::get<1>(contentLength);
          buffer[5] = std::get<0>(contentLength);
          buffer[6] = '\0';
          buffer[7] = '\0';

          this->connection->write(buffer, Constants::Limits::HEADER_LENGTH);
          this->connection->write(data.c_str(), data.length());
        }
      };
    }
  }
}