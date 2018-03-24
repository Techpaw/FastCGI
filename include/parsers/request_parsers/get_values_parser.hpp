#pragma once

#include <header_type.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class GetValuesParser : public AbstractParser {
        void parse(RequestPointer request, State& bodyState, State& HeaderState) override {

        }

        bool mayParse(RequestPointer request, State& bodyState, State& HeaderState) override {
          return request->getHeader().getType() == HeaderType::GET_VALUES;
        }
      };
    }
  }
}