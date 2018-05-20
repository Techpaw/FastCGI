#include <fastcgi/builders/response_builder.hpp>

namespace Fcgi {
  namespace Builders {
    ResponseBuilder::ResponseBuilder(
      const Pointers::ConnectionPointer& connection,
      const Pointers::ResponsePointer& response
    ) :
      connection{connection},
      response{response}
    {}

    ResponseBuilders::OutBuilder ResponseBuilder::stdout() {
      return ResponseBuilders::OutBuilder(
          this->connection,
          this->response,
          ResponseBuilders::OutBuilder::TYPE::STDOUT
      );
    }

    ResponseBuilders::OutBuilder ResponseBuilder::stderr() {
      return ResponseBuilders::OutBuilder(
          this->connection,
          this->response,
          ResponseBuilders::OutBuilder::TYPE::STDERR
      );
    }

    ResponseBuilders::EndRequestBuilder ResponseBuilder::end() {
      return ResponseBuilders::EndRequestBuilder(
          this->connection,
          this->response
      );
    }

    ResponseBuilders::GetValuesBuilder ResponseBuilder::values() {
      return ResponseBuilders::GetValuesBuilder(
          this->connection,
          this->response
      );
    }
  }
}