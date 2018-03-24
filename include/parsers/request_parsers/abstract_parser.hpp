#pragma once

#include <state.hpp>
#include <request.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class AbstractParser {
      public:
        virtual void parse(RequestPointer request, State& bodyState, State& HeaderState) = 0;
        virtual bool mayParse(RequestPointer request, State& bodyState, State& HeaderState) = 0;
        virtual ~AbstractParser() = default;
      };
    }
  }
}