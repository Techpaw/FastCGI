#include <fastcgi/builders/response_builders/out_builder.hpp>

namespace Fcgi {
  namespace Builders {
    namespace ResponseBuilders {
      OutBuilder::OutBuilder(
        Pointers::ConnectionPointer& connection,
        Pointers::ResponsePointer& response,
        TYPE type
      ) : BaseBuilder{connection, response},
          type{type}
      {}

      void OutBuilder::build() {
        Buffer& data = this->dataSource();

        while (!data.eof()) {
          this->sendPortion(data.readData(Constants::Limits::MAX_PORTION_LENGTH));
        }

        this->sendPortion("");
      }

      Buffer& OutBuilder::dataSource() {
        if (this->type == TYPE::STDOUT) {
          return this->response->getBody().getBody();
        }

        return this->response->getBody().getError();
      }

      Constants::Header OutBuilder::headerType() {
        if (this->type == TYPE::STDOUT) {
          return Constants::Header::STDOUT;
        }

        return Constants::Header::STDERR;
      }

      void OutBuilder::sendPortion(std::string portion) {
        this->sendHeader(this->headerType(), (std::uint16_t) portion.length());
        this->connection->write(portion.c_str(), (std::uint32_t) portion.length());
      }
    }
  }
}