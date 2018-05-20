#include <fastcgi/parsers/request_parsers/body_parsing_chain.hpp>

namespace Fcgi {
  namespace Parsers {
    namespace RequestParsers {
      BodyParsingChain::BodyParsingChain() {
        this->add(std::make_unique<BeginRequestParser>(BeginRequestParser()));
        this->add(std::make_unique<ParamsParser>(ParamsParser()));
        this->add(std::make_unique<StdinParser>(StdinParser()));
        this->add(std::make_unique<DataParser>(DataParser()));
        this->add(std::make_unique<GetValuesParser>(GetValuesParser()));
      }

      void BodyParsingChain::add(std::unique_ptr<AbstractParser> parser) {
        this->parsersList.push_back(std::move(parser));
      }

      void BodyParsingChain::parse(
        const Pointers::RequestPointer& request,
        State& headerState,
        State& bodyState
      ) {
        auto it = this->parsersList.begin();

        for (; it != this->parsersList.end(); ++it) {
          if ((*it)->mayParse(request, headerState, bodyState)) {
            (*it)->parse(request, headerState, bodyState);
          }
        }
      }
    }
  }
}