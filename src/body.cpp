#include <fastcgi/body.hpp>

namespace Fcgi {
  Body::Body() : data{Buffer()}, body{Buffer()}, error{Buffer()} {}

  void Body::setRole(Constants::RoleType role) {
    this->role = role;
  }

  Constants::RoleType& Body::getRole() {
    return this->role;
  }

  void Body::setFlags(std::uint8_t flags) {
    this->flags = flags;
  }

  std::uint8_t Body::getFlags() {
    return this->flags;
  }

  void Body::setParams(std::map<std::string, std::string>& params) {
    this->params = params;
  }

  void Body::setParams(std::map<std::string, std::string> params) {
    this->params.insert(params.begin(), params.end());
  }

  void Body::setParam(std::string name, std::string value) {
    this->params[name] = value;
  }

  std::map<std::string, std::string> Body::getParams() {
    return this->params;
  }

  std::string Body::getParam(const std::string& name) {
    return this->params[name];
  }

  void Body::setBody(const char* data, std::size_t length) {
    this->body.setData(data, length);
  }

  void Body::appendBody(const char* body, std::size_t length) {
    this->body.appendData(body, length);
  }

  Buffer& Body::getBody() {
    return this->body;
  }

  void Body::setError(const char* error, std::size_t length) {
    this->error.setData(error, length);
  }

  void Body::appendError(const char* error, std::size_t length) {
    this->error.appendData(error, length);
  }

  Buffer& Body::getError() {
    return this->error;
  }

  void Body::setData(const char* data, std::size_t length) {
    this->data.setData(data, length);
  }

  void Body::appendData(const char* data, std::size_t length) {
    this->data.appendData(data, length);
  }

  Buffer& Body::getData() {
    return this->data;
  }
}