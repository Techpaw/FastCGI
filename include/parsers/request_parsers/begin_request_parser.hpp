#pragma once

#include <header_type.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>
#include <calculators/bytes_reducer.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class BeginRequestParser : public AbstractParser {
        void parse(RequestPointer request, State& bodyState, State& HeaderState) override {
          request->getBody().setFlags((std::uint8_t) bodyState.getBuffer()[2]);
          request->getBody().setRole((RoleType) Calculators::BytesReducer::reduce16(bodyState.getBuffer()));
        }

        bool mayParse(RequestPointer request, State& bodyState, State& HeaderState) override {
          return request->getHeader().getType() == HeaderType::BEGIN_REQUEST;
        }
      };
    }
  }
}