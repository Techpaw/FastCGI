#pragma once

#include <map>
#include <string>
#include <buffer.hpp>
#include <constants/role_type.hpp>

namespace Fcgi {
  class Body {
  public:
    explicit Body();

    void setRole(Constants::RoleType role);
    Constants::RoleType& getRole();
    void setFlags(std::uint8_t flags);
    std::uint8_t getFlags();
    void setParams(std::map<std::string, std::string>& params);
    void setParams(std::map<std::string, std::string> params);
    void setParam(std::string name, std::string value);
    std::map<std::string, std::string> getParams();
    std::string getParam(const std::string& name);
    void setBody(const char* data, std::size_t length);
    void appendBody(const char* body, std::size_t length);
    Buffer& getBody();
    void setError(const char* error, std::size_t length);
    void appendError(const char* error, std::size_t length);
    Buffer& getError();
    void setData(const char* data, std::size_t length);
    void appendData(const char* data, std::size_t length);
    Buffer& getData();
  private:
    Buffer data;
    Buffer body;
    Buffer error;
    std::map<std::string, std::string> params;
    std::uint8_t flags;
    Constants::RoleType role;
  };
}