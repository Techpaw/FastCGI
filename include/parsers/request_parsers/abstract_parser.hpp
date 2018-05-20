#pragma once

#include <state.hpp>
#include <request.hpp>
#include <pointers/request_pointer.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class AbstractParser {
      public:
        virtual void parse(
          Pointers::RequestPointer request,
          State& bodyState,
          State& HeaderState
        ) = 0;

        virtual bool mayParse(
          Pointers::RequestPointer request,
          State& bodyState,
          State& HeaderState
        ) = 0;

        virtual ~AbstractParser() = default;
      };
    }
  }
}