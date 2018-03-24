#pragma once

#include <header_type.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>
#include <calculators/bytes_reducer.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class DataParser : public AbstractParser {
        void parse(RequestPointer request, State& bodyState, State& HeaderState) override {
          request->getBody().appendData(bodyState.getBuffer(), bodyState.getBytesReceived());
        }

        bool mayParse(RequestPointer request, State& bodyState, State& HeaderState) override {
          return request->getHeader().getType() == HeaderType::DATA;
        }
      };
    }
  }
}