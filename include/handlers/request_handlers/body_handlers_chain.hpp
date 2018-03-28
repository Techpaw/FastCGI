#pragma once

#include <pointers/connection_pointer.hpp>
#include <pointers/response_pointer.hpp>
#include <handlers/request_handlers/abstract_handler.hpp>
#include <handlers/request_handlers/invalid_role_handler.hpp>
#include <handlers/request_handlers/get_values_handler.hpp>
#include <handlers/request_handlers/complete_request_handler.hpp>
#include <handlers/request_handlers/fallback_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class BodyHandlersChain : public AbstractHandler {
      public:
        explicit BodyHandlersChain() {
          this->add(new FallbackHandler());
          this->add(new InvalidRoleHandler());
          this->add(new GetValuesHandler());
          this->add(new CompleteRequestHandler());
        }

        void add(AbstractHandler* parser) {
          this->handlersList.push_back(parser);
        }

        void handle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) {
          std::list<AbstractHandler*>::iterator it;

          for (it = this->handlersList.begin(); it != this->handlersList.end(); ++it) {
            AbstractHandler* x = (*it);
            if ((*it)->mayHandle(connection, request, response)) {
              (*it)->handle(connection, request, response);
//              break;
            }
          }
        }

        bool mayHandle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) {
          return true;
        }

        ~BodyHandlersChain() {
          std::list<AbstractHandler*>::iterator it;

          for (it = this->handlersList.begin(); it != this->handlersList.end(); ++it) {
            delete *it;
          }
        }
      private:
        std::list<AbstractHandler*> handlersList;
      };
    };
  }
}