#include <string>
#include <iostream>
#include <connection.hpp>
#include <response.hpp>
#include <handlers/request_handlers/body_handler.hpp>
#include <protocol_status_type.hpp>
#include <builders/response_builders/stdout_builder.hpp>
#include <builders/response_builders/end_request_builder.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  namespace Handlers {
    namespace RequestHandlers {
      BodyHandler::BodyHandler() {
//          this->bodyParser = Parsers::RequestParsers::BodyParsingChain();
      }

      void BodyHandler::handle(Pointers::ConnectionPointer& connection, RequestPointer& request) {
        if (request->getHeader().() == HeaderType::STDIN) {

        }
        if (request->getHeader().getType() == HeaderType::STDIN && request->getHeader().getBodyLength() == 0) {
          // @todo run middlewares here
          // @todo save and read stdout from tmpfile
          std::string text = "Content-type: text/html; charset=utf-8\r\n\r\n<html><head></head><body>Привет МИР</body></html>";
          Pointers::ResponsePointer response;
          response.reset(new Response());
          response->getHeader().setType(HeaderType::STDOUT);
          response->getBody().setData(text.c_str(), text.length());
          response->getHeader().setRequestId(request->getHeader().getRequestId());
          response->setAppStatus(200);
          response->setprotocolStatus(ProtocolStatusType::REQUEST_COMPLETE);

          Builders::ResponseBuilders::StdoutBuilder(connection, response).build();
          Builders::ResponseBuilders::EndRequestBuilder(connection, response).build();
        } else {
          bodyParser.parse(request,
            connection->getBodyState(),
            connection->getHeaderState()
          );
          connection->start();
        }
      };
    }
  }
}