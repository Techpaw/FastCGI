#pragma once

#include <header_type.hpp>

namespace Fcgi {
  class Header {
  public:
    void setVersion(std::uint8_t version) {
      this->version = version;
    }

    std::uint8_t getVersion() {
      return this->version;
    };

    void setType(HeaderType type) {
      this->type = type;
    }

    HeaderType& getType() {
      return this->type;
    }

    void setRequestId(std::uint16_t requestId) {
      this->requestId = requestId;
    }

    std::uint16_t getRequestId() {
      return this->requestId;
    }

    void setContentLength(std::uint16_t length) {
      this->contentLength = length;
    }

    std::uint16_t getContentLength() {
      return this->contentLength;
    }

    void setPaddingLength(std::uint8_t length) {
      this->paddingLength = length;
    }

    std::uint8_t getPaddingLength() {
      return this->paddingLength;
    }

    void setReserved(std::uint8_t length) {
      this->reserved = length;
    }

    std::uint8_t getReserved() {
      return this->reserved;
    }

    unsigned int getBodyLength() {
      return this->contentLength + this->paddingLength;
    }

  private:
    std::uint8_t version;
    HeaderType type;
    std::uint16_t requestId;
    std::uint16_t contentLength;
    std::uint8_t paddingLength;
    std::uint8_t reserved;
  };
}