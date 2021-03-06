#pragma once

#include <fastcgi/header.hpp>
#include <fastcgi/body.hpp>

namespace Fcgi {
  class Request {
  public:
    explicit Request();
    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;

    Header& getHeader();
    Body& getBody();
  private:
    Header header;
    Body body;
  };
}