#pragma once

#include <header.hpp>
#include <body.hpp>

namespace Fcgi {
  class Request {
  public:
    explicit Request(): header{Header()}, body{Body()} {};
    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;

//    void setHeader(Header& header) {
//      this->header = header;
//    }

    Header& getHeader() {
      return this->header;
    }

//    void setBody(Body& body) {
//      this->body = body;
//    }

    Body& getBody() {
      return this->body;
    }
  private:
    Header header;
    Body body;
  };

  typedef std::shared_ptr<Request> RequestPointer;
}