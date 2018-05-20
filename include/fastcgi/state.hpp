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

    void setup(
        std::size_t bytesTransferred,
        std::size_t bytesReceived,
        const boost::system::error_code& errorCode
    );

    void allocateBuffer(std::size_t length);
    std::size_t getBytesTransferred();
    std::size_t getBytesReceived();
    boost::system::error_code& getErrorCode();
    char* getBuffer();
    ~State();
  private:
    char* buffer{nullptr};
    std::size_t bytesTransferred{0};
    std::size_t bytesReceived{0};
    boost::system::error_code errorCode{boost::system::error_code()};
  };
}