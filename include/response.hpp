#pragma once

#include <header.hpp>
#include <body.hpp>
#include <protocol_status_type.hpp>

namespace Fcgi {
  class Response {
  public:
    explicit Response(): body{Body()}, header{Header()} {};
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;

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

    void setAppStatus(std::uint32_t status) {
      this->appStatus = status;
    }

    std::uint32_t getAppStatus() {
      return this->appStatus;
    }

    void setprotocolStatus(ProtocolStatusType status) {
      this->protocolStatus = status;
    }

    ProtocolStatusType getProtocolStatus() {
      return this->protocolStatus;
    }
  private:
    Header header;
    Body body;
    std::uint32_t appStatus;
    ProtocolStatusType protocolStatus;
  };
}