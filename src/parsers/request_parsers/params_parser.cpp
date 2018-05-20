#include <parsers/request_parsers/params_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      void ParamsParser::parse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        std::map<std::string, std::string> map;
        this->parseRecursively(map, bodyState.getBuffer(), bodyState.getBytesReceived());
        request->getBody().setParams(std::move(map));
      }

      bool ParamsParser::mayParse(
        Pointers::RequestPointer request,
        State& bodyState,
        State& HeaderState
      ) {
        return request->getHeader().getType() == Constants::Header::PARAMS;
      }

      void ParamsParser::parseRecursively(
        std::map<std::string, std::string>& map,
        const char* str,
        std::size_t length,
        std::size_t offset
      ) {
        std::uint32_t nameLength = 0;
        std::uint32_t valueLength = 0;
        std::uint8_t offsetLength = 0;
        std::size_t paramLength = 0;

        if (length < Constants::Limits::MIN_PARAMS_LENGTH) {
          return;
        }

        std::tie(nameLength, valueLength, offsetLength) = this->calculateLengths(str, length, offset);
        this->parseParameter(map, nameLength, valueLength, str, offset + offsetLength);
        paramLength = nameLength + valueLength + offsetLength;

        if (paramLength < length) {
          return this->parseRecursively(map, str, length - paramLength, offset + paramLength);
        }
      }

      std::tuple<std::uint32_t, std::uint32_t, std::uint8_t>
      ParamsParser::calculateLengths(
        const char* str,
        std::size_t& length,
        std::size_t offset
      ) {
        std::uint32_t nameLength = 0;
        std::uint32_t valueLength = 0;
        std::uint8_t offsetLength = 0;

        if (this->has_short_name_and_value(str, offset)) {
          nameLength = (std::uint8_t) str[offset];
          valueLength = (std::uint8_t) str[offset + 1];
          offsetLength = 2;
        } else if (this->has_short_name_and_long_value(str, offset)) {
          nameLength = (std::uint8_t) str[offset];
          valueLength = Calculators::BytesReducer::reduce32(str, offset + 1);
          offsetLength = 5;
        } else if (this->has_long_name_and_short_value(str, offset)) {
          nameLength = Calculators::BytesReducer::reduce32(str, offset);
          valueLength = (std::uint8_t) str[offset + 4];
          offsetLength = 5;
        } else if (this->has_long_name_and_long_value(str, offset)) {
          nameLength = Calculators::BytesReducer::reduce32(str, offset);
          valueLength = Calculators::BytesReducer::reduce32(str, offset + 4);
          offsetLength = 8;
        } else {
          raise_exception(Fcgi::Exceptions::BadParamsException("Params name/value pair could not be calculated"));
        }

        this->checkPairLength(nameLength + valueLength + offsetLength, length, offset);

        return std::make_tuple(nameLength, valueLength, offsetLength);
      };

      void ParamsParser::checkPairLength(std::size_t expected, std::size_t actual, std::size_t offset) {
        if (actual < expected) {
          raise_exception(Fcgi::Exceptions::BadParamsException("Unexpected param length received"));
        }
      }

      void ParamsParser::parseParameter(
        std::map<std::string, std::string>& map,
        uint32_t& nameLength,
        uint32_t& valueLength,
        const char* str,
        std::size_t offset
      ) {
        std::string name;
        std::string value;

        name.assign(str + offset, nameLength);
        value.assign(str + offset + nameLength, valueLength);

        map[name] = value;
      }

      bool ParamsParser::is_short(const char* str, std::size_t offset) {
        auto byte = (std::uint8_t) str[offset];
        return byte >> 7 == 0;
      }

      bool ParamsParser::is_long(const char* str, std::size_t offset) {
        auto byte = (std::uint8_t) str[offset];
        return byte >> 7 == 1;
      }

      bool ParamsParser::has_short_name_and_value(const char* str, std::size_t& offset) {
        return this->is_short(str, offset) && this->is_short(str, offset + 1);
      }

      bool ParamsParser::has_short_name_and_long_value(const char* str, std::size_t& offset) {
        return this->is_short(str, offset) && this->is_long(str, offset + 1);
      }

      bool ParamsParser::has_long_name_and_short_value(const char* str, std::size_t& offset) {
        return this->is_long(str, offset) && this->is_short(str, offset + 4);
      }

      bool ParamsParser::has_long_name_and_long_value(const char* str, std::size_t& offset) {
        return this->is_long(str, offset) && this->is_long(str, offset + 4);
      }
    }
  }
}