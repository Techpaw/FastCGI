#include <application.hpp>

namespace Fcgi {
  Application& Application::instance() {
    static Application instance;
    return instance;
  }

  void Application::set(std::shared_ptr<ApplicationInterface> application) {
    this->application = application;
  }

  void Application::execute(
      const Pointers::ConnectionPointer& connection,
      const Pointers::RequestPointer& request,
      const Pointers::ResponsePointer& response
  ) {
    this->application->execute(connection, request, response);
  }
}