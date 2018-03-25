#pragma once

#include <map>
#include <string>
#include <role_type.hpp>
#include <buffer.hpp>

namespace Fcgi {
  class Body {
  public:
    explicit Body() : data{Buffer()}, body{Buffer()}, error{Buffer()} {}

    void setRole(RoleType role) {
      this->role = role;
    }

    RoleType& getRole() {
      return this->role;
    }

    void setFlags(std::uint8_t flags) {
      this->flags = flags;
    }

    std::uint8_t getFlags() {
      return this->flags;
    }

    void setParams(std::map<std::string, std::string>& params) {
      this->params = params;
    }

    void setParams(std::map<std::string, std::string> params) {
      this->params.insert(params.begin(), params.end());
    }

    void setParam(std::string name, std::string value) {
      this->params[name] = value;
    }

    std::map<std::string, std::string> getParams() {
      return this->params;
    }

    std::string getParam(const std::string& name) {
      return this->params[name];
    }

    void setBody(const char* data, std::size_t length) {
      this->body.setData(data, length);
    }

    void appendBody(const char* body, std::size_t length) {
      this->body.appendData(body, length);
    }

    Buffer& getBody() {
      return this->body;
    }

    void setError(const char* error, std::size_t length) {
      this->error.setData(error, length);
    }

    void appendError(const char* error, std::size_t length) {
      this->error.appendData(error, length);
    }

    Buffer& getError() {
      return this->error;
    }

    void setData(const char* data, std::size_t length) {
      this->data.setData(data, length);
    }

    void appendData(const char* data, std::size_t length) {
      this->data.appendData(data, length);
    }

    Buffer& getData() {
      return this->data;
    }
  private:
    Buffer data;
    Buffer body;
    Buffer error;
    std::map<std::string, std::string> params;
    std::uint8_t flags;
    RoleType role;
  };
}