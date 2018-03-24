#include <string>
#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>

#include <exceptions/basic_exception.hpp>

namespace Fcgi {
  namespace Exceptions {
    BasicException::BasicException(std::string str) {
      this->info = std::move(str);
      this->stacktrace = boost::stacktrace::stacktrace();
    }

    const char* BasicException::what() const noexcept {
      std::string error;

      error.append(this->info);
      error.append("\n");
      error.append(boost::diagnostic_information_what(*this));

      return error.c_str();
    }

    const boost::stacktrace::stacktrace BasicException::getStacktrace() const noexcept {
      return this->stacktrace;
    }
  }
}