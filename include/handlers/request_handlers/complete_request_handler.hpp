#pragma once

#include <header_type.hpp>
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
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          auto x = this->mayHandle(connection, request, response);
          auto rb = Builders::ResponseBuilder(connection, response);

          // @todo run middlewares here
          // @todo save and read stdout from tmpfile
          std::string text = "Content-type: text/html; charset=utf-8\r\n\r\nHELLO";

          response->getHeader().setType(HeaderType::STDOUT);
          response->getBody().setBody(text.c_str(), text.length());
          response->getHeader().setRequestId(request->getHeader().getRequestId());
          // @todo move app statuses to consts or enums
          response->setAppStatus(200);
          response->setprotocolStatus(ProtocolStatusType::REQUEST_COMPLETE);

          rb.stdout().build();
          rb.end().build(this->closeAfterWrite(request));
        }

        bool mayHandle(
            const Pointers::ConnectionPointer& connection,
            const RequestPointer& request,
            Pointers::ResponsePointer& response
        ) override {
          return request->getHeader().getType() == HeaderType::ABORT_REQUEST ||
            this->lastPortionReceived(request);
        }

        bool stopOnHandle() override {
          return true;
        }

      private:
        bool lastPortionReceived(const RequestPointer& request) {
          return request->getHeader().getType() == HeaderType::STDIN &&
            request->getHeader().getBodyLength() == 0;
        }
      };
    }
  }
}