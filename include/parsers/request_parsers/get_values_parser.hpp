#pragma once

#include <constants/header.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class GetValuesParser : public AbstractParser {
        void parse(
          Pointers::RequestPointer request,
          State& bodyState,
          State& HeaderState
        ) override;

        bool mayParse(
          Pointers::RequestPointer request,
          State& bodyState,
          State& HeaderState
        ) override;
      };
    }
  }
}