#pragma once

#include <application.hpp>
#include <constants/header.hpp>
#include <configuration.hpp>
#include <constants/flags.hpp>
#include <calculators/bytes_reducer.hpp>
#include <builders/response_builder.hpp>
#include <handlers/request_handlers/abstract_handler.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      class CompleteRequestHandler : public AbstractHandler {
      public:
        void handle(
          const Pointers::ConnectionPointer& connection,
          const Pointers::RequestPointer& request,
          const Pointers::ResponsePointer& response
        ) override;

        bool mayHandle(
          const Pointers::ConnectionPointer& connection,
          const Pointers::RequestPointer& request,
          const Pointers::ResponsePointer& response
        ) override;

        bool stopOnHandle() override;
      private:
        bool lastPortionReceived(const Pointers::RequestPointer&);
      };
    }
  }
}