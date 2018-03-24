#pragma once

#include <boost/system/error_code.hpp>

namespace Fcgi {
  class State {
  public:
    State() = default;
    State(State&) = default;
    State& operator=(State&&) = default;
    State(State&&) = default;

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    void allocateBuffer(std::size_t length) {
      delete[] this->buffer;
      this->buffer = new char[length];
    }

    void setup(
        std::size_t bytesTransferred,
        std::size_t bytesReceived,
        const boost::system::error_code& errorCode
    ) {
      this->bytesTransferred = bytesTransferred;
      this->bytesReceived = bytesReceived;
      this->errorCode = errorCode;
    }

    std::size_t getBytesTransferred() {
      return this->bytesTransferred;
    }

    std::size_t getBytesReceived() {
      return this->bytesReceived;
    }

    boost::system::error_code& getErrorCode() {
      return this->errorCode;
    }

    char* getBuffer() {
      return this->buffer;
    }

    ~State() {
      delete[] this->buffer;
    }
  private:
    char* buffer{nullptr};
    std::size_t bytesTransferred{0};
    std::size_t bytesReceived{0};
    boost::system::error_code errorCode{boost::system::error_code()};
  };
}