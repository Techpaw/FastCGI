#pragma once

#include <header.hpp>
#include <body.hpp>

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