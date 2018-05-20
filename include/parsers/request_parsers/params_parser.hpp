#pragma once

#include <map>
#include <tuple>

#include <constants/header.hpp>
#include <constants/limits.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>
#include <calculators/bytes_reducer.hpp>
#include <exceptions/exceptions.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class ParamsParser : public AbstractParser {
      public:
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

      private:
        void parseRecursively(
          std::map<std::string, std::string>&,
          const char* str,
          std::size_t length,
          std::size_t offset = 0
        );

        std::tuple<std::uint32_t, std::uint32_t, std::uint8_t>
        calculateLengths(
          const char* str,
          std::size_t& length,
          std::size_t offset
        );

        void checkPairLength(
          std::size_t expected,
          std::size_t actual,
          std::size_t offset
        );

        void parseParameter(
          std::map<std::string, std::string>& map,
          uint32_t& nameLength,
          uint32_t& valueLength,
          const char* str,
          std::size_t offset
        );

        bool is_short(const char* str, std::size_t offset);
        bool is_long(const char* str, std::size_t offset);
        bool has_short_name_and_value(const char* str, std::size_t& offset);
        bool has_short_name_and_long_value(const char* str, std::size_t& offset);
        bool has_long_name_and_short_value(const char* str, std::size_t& offset);
        bool has_long_name_and_long_value(const char* str, std::size_t& offset);
      };
    }
  }
}