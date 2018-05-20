#pragma once

#include <map>
#include <string>
#include <constants/role_type.hpp>
#include <boost/lexical_cast.hpp>

namespace Fcgi {
  class Configuration {
  public:
    static Configuration& instance();

    static void set(std::string name, std::string value);
    std::string& operator[] (const std::string name);

    template <typename T>
    static T get(std::string name) {
      return boost::lexical_cast<T>(Configuration::instance()[std::move(name)]);
    }
  private:
    std::map<std::string, std::string> map;
    explicit Configuration();
  };
}