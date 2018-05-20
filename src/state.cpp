#include <fastcgi/state.hpp>

namespace Fcgi {
  void State::allocateBuffer(std::size_t length) {
    delete[] this->buffer;
    this->buffer = new char[length];
  }

  void State::setup(
    std::size_t bytesTransferred,
    std::size_t bytesReceived,
    const boost::system::error_code& errorCode
  ) {
    this->bytesTransferred = bytesTransferred;
    this->bytesReceived = bytesReceived;
    this->errorCode = errorCode;
  }

  std::size_t State::getBytesTransferred() {
    return this->bytesTransferred;
  }

  std::size_t State::getBytesReceived() {
    return this->bytesReceived;
  }

  boost::system::error_code& State::getErrorCode() {
    return this->errorCode;
  }

  char* State::getBuffer() {
    return this->buffer;
  }

  State::~State() {
    delete[] this->buffer;
  }
}