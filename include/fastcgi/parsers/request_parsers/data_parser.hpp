#pragma once

#include <fastcgi/constants/header.hpp>
#include <fastcgi/parsers/request_parsers/abstract_parser.hpp>
#include <fastcgi/calculators/bytes_reducer.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class DataParser : public AbstractParser {
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