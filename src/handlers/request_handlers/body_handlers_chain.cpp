#include <handlers/request_handlers/body_handlers_chain.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      BodyHandlersChain::BodyHandlersChain() {
        this->add(std::make_unique<BodyParserHandler>());
        this->add(std::make_unique<InvalidRoleHandler>());
        this->add(std::make_unique<GetValuesHandler>());
        this->add(std::make_unique<CompleteRequestHandler>());
        this->add(std::make_unique<FallbackHandler>());
      }

      void BodyHandlersChain::add(std::unique_ptr<AbstractHandler> handler) {
        this->handlersList.push_back(std::move(handler));
      }

      void BodyHandlersChain::handle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        std::list<std::unique_ptr<AbstractHandler>>::iterator it;

        for (it = this->handlersList.begin(); it != this->handlersList.end(); ++it) {
          if ((*it)->mayHandle(connection, request, response)) {
            (*it)->handle(connection, request, response);

            if ((*it)->stopOnHandle()) {
              break;
            }
          }
        }
      }

      bool BodyHandlersChain::mayHandle(
        const Pointers::ConnectionPointer& connection,
        const Pointers::RequestPointer& request,
        const Pointers::ResponsePointer& response
      ) {
        return true;
      }
    }
  }
}