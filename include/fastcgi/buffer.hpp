#pragma once

#include <string>
#include <sstream>
#include <cstring>

#include <fastcgi/constants/limits.hpp>

namespace Fcgi {
  /**
   * That's a memory/file-based buffer, which allows to keep
   * Constants::Limits::MAX_IN_MEMORY_BUFFER_SIZE bytes of data in memory
   * and then drop this data to file when exceeding this limit.
   *
   * NOTE that the ile data is kept in temporary files, so this buffer should
   * not be used to keep long-life data.
   */
  class Buffer {
  public:
    explicit Buffer();
    void setData(const char* data, std::size_t length);
    void appendData(const char* data, std::size_t length);
    std::string readData(std::size_t length);
    std::string readLine();
    void rewind();
    bool eof();
  private:
    std::FILE* dataFile;
    std::string dataBuffer;
    std::istringstream dataStream;
    std::size_t dataLength;
    bool fileMode;
  };
}