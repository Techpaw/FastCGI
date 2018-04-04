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

          // @todo add parser handler here
          this->add(std::make_unique<InvalidRoleHandler>());
          this->add(std::make_unique<GetValuesHandler>());
          this->add(std::make_unique<CompleteRequestHandler>());
          this->add(std::make_unique<FallbackHandler>());
        }

        void add(std::unique_ptr<AbstractHandler> handler) {
          this->handlersList.push_back(std::move(handler));
        }

        void handle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) {
          std::list<std::unique_ptr<AbstractHandler>>::iterator it;

          for (it = this->handlersList.begin(); it != this->handlersList.end(); ++it) {
            auto handler = std::move(*it);

            if ((*it)->mayHandle(connection, request, response)) {
              (*it)->handle(connection, request, response);

              if ((*it)->stopOnHandle()) {
                break;
              }
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

//        ~BodyHandlersChain() {
//          std::list<std::unique_ptr<AbstractHandler>>::iterator it;
//
//          for (it = this->handlersList.begin(); it != this->handlersList.end(); ++it) {
//            delete *it;
//          }
//        }
      private:
        std::list<std::unique_ptr<AbstractHandler>> handlersList;
      };
    };
  }
}