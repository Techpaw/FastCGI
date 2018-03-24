#pragma once

#include <string>
#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>

namespace Fcgi {
  namespace Exceptions {
    class BasicException : public virtual boost::exception, public virtual std::exception {
    public:
      BasicException() = default;
      explicit BasicException(std::string str);
      virtual const char* what() const noexcept override;
      virtual const boost::stacktrace::stacktrace getStacktrace() const noexcept;
    private:
      std::string info;
      boost::stacktrace::stacktrace stacktrace;
    };
  }
}