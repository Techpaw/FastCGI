#include <buffer.hpp>

namespace Fcgi {
  Buffer::Buffer() : fileMode{false}, dataFile{nullptr}, dataLength{0} {};

  void Buffer::setData(const char* data, std::size_t length) {
    if (length > Constants::Limits::MAX_IN_MEMORY_BUFFER_SIZE) {
      this->dataFile = std::tmpfile();
      this->dataLength = length;
      this->fileMode = true;
      std::fputs(data, this->dataFile);
    } else {
      this->dataBuffer.assign(data);
      this->dataStream.str(this->dataBuffer);
      this->dataLength = this->dataBuffer.length();
    }

    this->rewind();
  }

  void Buffer::appendData(const char* data, std::size_t length) {
    if (this->fileMode || this->dataLength + length > Constants::Limits::MAX_IN_MEMORY_BUFFER_SIZE) {
      if (this->dataFile == nullptr) {
        this->dataFile = std::tmpfile();
      }

      this->fileMode = true;
      this->dataLength += length;

      std::fseek(this->dataFile, 0, SEEK_END);
      std::fputs(this->dataBuffer.c_str(), this->dataFile);
      std::fputs(data, this->dataFile);

      this->dataBuffer.clear();
    } else {
      this->dataBuffer.append(data);
      this->dataStream.str(this->dataBuffer);
      this->dataLength = this->dataBuffer.length();
    }

    this->rewind();
  }

  std::string Buffer::readData(std::size_t length) {
    char* buffer = new char[length];
    std::string stringBuffer;

    if (this->fileMode) {
      std::fread(buffer, 1, length, this->dataFile);
      stringBuffer.assign(buffer);

      delete[] buffer;
      return stringBuffer;
    }

    this->dataStream.read(buffer, length);
    stringBuffer.assign(buffer);

    delete[] buffer;
    return stringBuffer;
  }

  std::string Buffer::readLine() {
    std::string line;

    if (this->fileMode) {
      long int currentPosition = ftell(this->dataFile);
      std::uint16_t bufferStep = Constants::Limits::MAX_IN_MEMORY_BUFFER_STEP;
      std::uint32_t currentLength = bufferStep;
      char* buffer = new char[bufferStep];
      char* newLinePos;

      while (true) {
        std::fseek(this->dataFile, currentPosition, SEEK_SET);
        std::fgets(buffer, currentLength, this->dataFile);

        if (
            (bool) std::feof(this->dataFile) ||
            (bool) std::ferror(this->dataFile) ||
            buffer[currentLength - 2] == '\n' ||
            buffer[currentLength - 2] == '\0'
            ) {
          break;
        }

        delete[] buffer;
        currentLength += bufferStep;
        buffer = new char[currentLength];
      }

      newLinePos = std::strchr(buffer, '\n');

      if ((bool) newLinePos) {
        *newLinePos = '\0';
      }

      line.assign(buffer);
      delete[] buffer;
    } else {
      std::getline(this->dataStream, line);
    }

    return line;
  }

  void Buffer::rewind() {
    if (this->fileMode) {
      std::rewind(this->dataFile);
    } else {
      this->dataStream.clear();
      this->dataStream.seekg(0, std::ios::beg);
    }
  }


  bool Buffer::eof() {
    if (dataLength == 0) {
      return true;
    }

    if (this->fileMode) {
      return (bool) std::feof(this->dataFile);
    }

    return this->dataStream.eof();
  }
}