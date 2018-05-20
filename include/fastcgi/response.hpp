#pragma once

#include <fastcgi/header.hpp>
#include <fastcgi/body.hpp>
#include <fastcgi/constants/protocol_status.hpp>
#include <fastcgi/constants/application_status.hpp>

namespace Fcgi {
  class Response {
  public:
    explicit Response(): body{Body()}, header{Header()} {};
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;

    Header& getHeader() {
      return this->header;
    }

    Body& getBody() {
      return this->body;
    }

    void setAppStatus(Constants::ApplicationStatus status) {
      this->appStatus = status;
    }

    Constants::ApplicationStatus getAppStatus() {
      return this->appStatus;
    }

    void setProtocolStatus(Constants::ProtocolStatus status) {
      this->protocolStatus = status;
    }

    Constants::ProtocolStatus getProtocolStatus() {
      return this->protocolStatus;
    }
  private:
    Header header;
    Body body;
    Constants::ApplicationStatus appStatus;
    Constants::ProtocolStatus protocolStatus;
  };
}