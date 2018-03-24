#pragma once

namespace Fcgi {
  class Configuration {
  public:
    MAX_CONNECTIONS = 16;
    MAX_REQUESTS = 20;
  private:
    Configuration() = default;
  };
}