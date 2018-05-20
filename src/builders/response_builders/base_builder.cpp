#include <builders/response_builders/base_builder.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      BaseBuilder::BaseBuilder(
        Pointers::ConnectionPointer& connection,
        Pointers::ResponsePointer& response
      ) :
        connection{connection},
        response{response}
      {}

      void BaseBuilder::sendHeader(
          Constants::Header headerType,
          std::uint16_t length
      ) {
        char buffer[Constants::Limits::HEADER_LENGTH];
        auto contentLength = Calculators::BytesExpander::expand16(length);
        auto requestId = Calculators::BytesExpander::expand16(
            this->response->getHeader().getRequestId()
        );

        buffer[0] = Constants::Versions::FCGI_VERSION;
        buffer[1] = (std::uint8_t) headerType;
        buffer[2] = std::get<1>(requestId);
        buffer[3] = std::get<0>(requestId);
        buffer[4] = std::get<1>(contentLength);
        buffer[5] = std::get<0>(contentLength);
        buffer[6] = '\0';
        buffer[7] = '\0';

        this->connection->write(buffer, Constants::Limits::HEADER_LENGTH);
      }
    }
  }
}