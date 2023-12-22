#include "utils.h"

bytes parseBytes(const std::string& byteStr) {
  bytes result;
  for(int i = 0; i < byteStr.size(); i += 2) {
    std::string byteString = byteStr.substr(i, 2);
    uint8_t byte = std::stoi(byteString, nullptr, 16);
    result.push_back(byte);
  }

  return result;
}
