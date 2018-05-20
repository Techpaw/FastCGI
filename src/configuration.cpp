#include <fastcgi/configuration.hpp>

namespace Fcgi {
  Configuration::Configuration() {
    this->map["FCGI_MAX_CONNS"] = "10";
    this->map["FCGI_MAX_REQS"] = "50";
    this->map["FCGI_MPXS_CONNS"] = "0";
    this->map["APPLICATION_TYPE"] = std::to_string((std::uint16_t) Constants::RoleType::RESPONDER);
  }

  Configuration& Configuration::instance() {
    static Configuration instance;
    return instance;
  }

  void Configuration::set(std::string name, std::string value) {
    Configuration::instance()[std::move(name)] = std::move(value);
  }

  std::string& Configuration::operator[] (const std::string name) {
    return this->map[name];
  }
}