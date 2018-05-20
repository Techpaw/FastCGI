#pragma once

#include <list>

#include <fastcgi/state.hpp>
#include <fastcgi/request.hpp>
#include <fastcgi/parsers/request_parsers/abstract_parser.hpp>
#include <fastcgi/parsers/request_parsers/begin_request_parser.hpp>
#include <fastcgi/parsers/request_parsers/params_parser.hpp>
#include <fastcgi/parsers/request_parsers/stdin_parser.hpp>
#include <fastcgi/parsers/request_parsers/data_parser.hpp>
#include <fastcgi/parsers/request_parsers/get_values_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class BodyParsingChain {
      public:
        explicit BodyParsingChain();

        void add(std::unique_ptr<AbstractParser> parser);
        void parse(const Pointers::RequestPointer&, State&, State&);
      private:
        std::list<std::unique_ptr<AbstractParser>> parsersList;
      };
    }
  }
}