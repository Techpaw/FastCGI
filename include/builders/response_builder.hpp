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
        const Pointers::ConnectionPointer&,
        const Pointers::ResponsePointer&
      );

      ResponseBuilders::OutBuilder stdout();
      ResponseBuilders::OutBuilder stderr();
      ResponseBuilders::EndRequestBuilder end();
      ResponseBuilders::GetValuesBuilder values();
    private:
      Pointers::ResponsePointer response;
      Pointers::ConnectionPointer connection;
    };
  }
}