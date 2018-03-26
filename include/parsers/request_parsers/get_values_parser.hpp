#pragma once

#include <header_type.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>

// @todo no need to keep this parser, as there's nothing to parse
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