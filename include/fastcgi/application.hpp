#pragma once

#include <fastcgi/pointers/response_pointer.hpp>
#include <fastcgi/pointers/request_pointer.hpp>
#include <fastcgi/pointers/connection_pointer.hpp>
#include <fastcgi/application_interface.hpp>

namespace Fcgi {
  class Application {
  public:
    static Application& instance();
    void set(std::shared_ptr<ApplicationInterface> application);

    void execute(
      const Pointers::ConnectionPointer& connection,
      const Pointers::RequestPointer& request,
      const Pointers::ResponsePointer& response
    );
  private:
    std::shared_ptr<ApplicationInterface> application;
  };
}