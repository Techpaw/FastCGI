#pragma once

#include <map>
#include <string>
#include <role_type.hpp>
#include <boost/lexical_cast.hpp>

namespace Fcgi {
  class Configuration {
  public:
    static Configuration& instance() {
      static Configuration instance;
      return instance;
    }

    template <typename T>
    static T get(std::string name) {
      return boost::lexical_cast<T>(Configuration::instance()[std::move(name)]);
    }

    static void set(std::string name, std::string value) {
      Configuration::instance()[std::move(name)] = std::move(value);
    }

    std::string& operator[] (const std::string name) {
      return this->map[std::move(name)];
    }
  private:
    std::map<std::string, std::string> map;

    explicit Configuration() {
      this->map["FCGI_MAX_CONNS"] = "10";
      this->map["FCGI_MAX_REQS"] = "50";
      this->map["FCGI_MPXS_CONNS"] = "0";
    }
  };
}