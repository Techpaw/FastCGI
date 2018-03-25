#include <string>
#include <iostream>
#include <connection.hpp>
#include <response.hpp>
#include <constants/flags.hpp>
#include <handlers/request_handlers/body_handler.hpp>
#include <protocol_status_type.hpp>
#include <builders/response_builder.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      BodyHandler::BodyHandler() : response{new Response()} {}

      void BodyHandler::handle(Pointers::ConnectionPointer& connection, RequestPointer& request) {
        if (this->paramsRequested(request)) {
          this->handleParamsRequested(connection, request);
        } else if (this->requestCompleted(request)) {
          this->handleRequestCompleted(connection, request);
        } else {
          bodyParser.parse(request,
            connection->getBodyState(),
            connection->getHeaderState()
          );
          connection->start();
        }
      };

      void BodyHandler::handleParamsRequested(Pointers::ConnectionPointer& connection, RequestPointer& request) {
        auto rb = Builders::ResponseBuilder(connection, this->response);
        rb.values().build();
      }

      void BodyHandler::handleRequestCompleted(Pointers::ConnectionPointer& connection, RequestPointer& request) {
        auto rb = Builders::ResponseBuilder(connection, this->response);

        // @todo run middlewares here
        // @todo save and read stdout from tmpfile
        std::string text = "Content-type: text/html; charset=utf-8\r\n\r\n";

        response->getHeader().setType(HeaderType::STDOUT);
        response->getBody().setBody(text.c_str(), text.length());
        response->getHeader().setRequestId(request->getHeader().getRequestId());
        response->setAppStatus(200);
        response->setprotocolStatus(ProtocolStatusType::REQUEST_COMPLETE);

        rb.stdout().build();
        rb.end().build(this->closeAfterWrite(request));
      }

      bool BodyHandler::closeAfterWrite(RequestPointer& request) {
        return (request->getBody().getFlags() & Constants::Flags::KEEP_CONN) == 0;
      }

      bool BodyHandler::lastPortionReceived(RequestPointer& request) {
        return request->getHeader().getType() == HeaderType::STDIN &&
          request->getHeader().getBodyLength() == 0;
      }

      bool BodyHandler::requestCompleted(RequestPointer& request) {
        return request->getHeader().getType() == HeaderType::ABORT_REQUEST ||
          this->lastPortionReceived(request);
      }

      bool BodyHandler::paramsRequested(RequestPointer& request) {
        return request->getHeader().getType() == HeaderType::GET_VALUES;
      }
    }
  }
}