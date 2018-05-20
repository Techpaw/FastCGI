#pragma once

#include <memory>
#include <constants/header.hpp>

namespace Fcgi {
  class Header {
  public:
    void setVersion(std::uint8_t version);
    std::uint8_t getVersion();
    void setType(Constants::Header type);
    Constants::Header& getType();
    void setRequestId(std::uint16_t requestId);
    std::uint16_t getRequestId();
    void setContentLength(std::uint16_t length);
    std::uint16_t getContentLength();
    void setPaddingLength(std::uint8_t length);
    std::uint8_t getPaddingLength();
    void setReserved(std::uint8_t length);
    std::uint8_t getReserved();
    unsigned int getBodyLength();
  private:
    std::uint8_t version;
    Constants::Header type;
    std::uint16_t requestId;
    std::uint16_t contentLength;
    std::uint8_t paddingLength;
    std::uint8_t reserved;
  };
}