#include <header.hpp>

namespace Fcgi {
  void Header::setVersion(std::uint8_t version) {
    this->version = version;
  }

  std::uint8_t Header::getVersion() {
    return this->version;
  };

  void Header::setType(Constants::Header type) {
    this->type = type;
  }

  Constants::Header& Header::getType() {
    return this->type;
  }

  void Header::setRequestId(std::uint16_t requestId) {
    this->requestId = requestId;
  }

  std::uint16_t Header::getRequestId() {
    return this->requestId;
  }

  void Header::setContentLength(std::uint16_t length) {
    this->contentLength = length;
  }

  std::uint16_t Header::getContentLength() {
    return this->contentLength;
  }

  void Header::setPaddingLength(std::uint8_t length) {
    this->paddingLength = length;
  }

  std::uint8_t Header::getPaddingLength() {
    return this->paddingLength;
  }

  void Header::setReserved(std::uint8_t length) {
    this->reserved = length;
  }

  std::uint8_t Header::getReserved() {
    return this->reserved;
  }

  unsigned int Header::getBodyLength() {
    return this->contentLength + this->paddingLength;
  }
}