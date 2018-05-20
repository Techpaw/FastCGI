#pragma once

#include <pointers/connection_pointer.hpp>
#include <pointers/request_pointer.hpp>
#include <pointers/response_pointer.hpp>

namespace Fcgi {
  class ApplicationInterface {
  public:
    /**
     * Execute middleware
     */
    virtual void execute(
      const Pointers::ConnectionPointer&,
      const Pointers::RequestPointer&,
      const Pointers::ResponsePointer&
    ) = 0;

    /**
     * Execute failure callback in case of
     * #execute() won't succeed
     */
    virtual void failure(
      const Pointers::ConnectionPointer&,
      const Pointers::RequestPointer&,
      const Pointers::ResponsePointer&,
      const std::exception&
    ) = 0;
  };
}