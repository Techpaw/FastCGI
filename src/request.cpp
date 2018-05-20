#include <request.hpp>

namespace Fcgi {
  Request::Request(): header{Header()}, body{Body()} {};

  Header& Request::getHeader() {
    return this->header;
  }

  Body& Request::getBody() {
    return this->body;
  }
}