#pragma once

#include <list>

#include <state.hpp>
#include <request.hpp>
#include <parsers/request_parsers/abstract_parser.hpp>
#include <parsers/request_parsers/begin_request_parser.hpp>
#include <parsers/request_parsers/params_parser.hpp>
#include <parsers/request_parsers/stdin_parser.hpp>
#include <parsers/request_parsers/data_parser.hpp>
#include <parsers/request_parsers/get_values_parser.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      class BodyParsingChain {
      public:
        explicit BodyParsingChain() {
          this->add(new BeginRequestParser());
          this->add(new ParamsParser());
          this->add(new StdinParser());
          this->add(new DataParser());
          this->add(new GetValuesParser());
        }

        void add(AbstractParser* parser) {
          this->parsersList.push_back(parser);
        }

        void parse(const RequestPointer& request, State& headerState, State& bodyState) {
          std::list<AbstractParser*>::iterator it;

          for (it = this->parsersList.begin(); it != this->parsersList.end(); ++it) {
            if ((*it)->mayParse(request, headerState, bodyState)) {
              (*it)->parse(request, headerState, bodyState);
            }
          }
        }

        ~BodyParsingChain() {
          std::list<AbstractParser*>::iterator it;

          for (it = this->parsersList.begin(); it != this->parsersList.end(); ++it) {
            delete *it;
          }
        }
      private:
        std::list<AbstractParser*> parsersList;
      };
    }
  }
}