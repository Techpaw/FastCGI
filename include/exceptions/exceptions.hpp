#pragma once

#include <boost/throw_exception.hpp>
#include <exceptions/basic_exception.hpp>

namespace Fcgi {
  namespace Exceptions {
    class BadParamsException : public BasicException {
      using BasicException::BasicException;
    };

    class InvalidBeginRequestBodyException : public BasicException {
      using BasicException::BasicException;
    };

    class InvalidHeaderException : public BasicException {
      using BasicException::BasicException;
    };

    class InvalidLengthException : public BasicException {
      using BasicException::BasicException;
    };
  }
}

#define raise_exception(ex) BOOST_THROW_EXCEPTION(ex)