#pragma once

#include <pointers/response_pointer.hpp>
#include <pointers/connection_pointer.hpp>
#include <builders/response_builders/out_builder.hpp>
#include <builders/response_builders/end_request_builder.hpp>
#include <builders/response_builders/get_values_builder.hpp>

namespace Fcgi {
  namespace Builders {
    class ResponseBuilder {
    public:
      explicit ResponseBuilder(
        Pointers::ConnectionPointer& connection,
        Pointers::ResponsePointer& response
      ) :
        connection{connection},
        response{response}
      {}

      ResponseBuilders::OutBuilder stdout() {
        return ResponseBuilders::OutBuilder(
          this->connection,
          this->response,
          ResponseBuilders::OutBuilder::TYPE::STDOUT
        );
      }

      ResponseBuilders::OutBuilder stderr() {
        return ResponseBuilders::OutBuilder(
          this->connection,
          this->response,
          ResponseBuilders::OutBuilder::TYPE::STDERR
        );
      }

      ResponseBuilders::EndRequestBuilder end() {
        return ResponseBuilders::EndRequestBuilder(
          this->connection,
          this->response
        );
      }

      ResponseBuilders::GetValuesBuilder values() {
        return ResponseBuilders::GetValuesBuilder(
          this->connection,
          this->response
        );
      }

    private:
      Pointers::ResponsePointer response;
      Pointers::ConnectionPointer connection;
    };
  }
}