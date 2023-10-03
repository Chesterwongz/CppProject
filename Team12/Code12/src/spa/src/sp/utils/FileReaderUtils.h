#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "sp/exceptions/SpException.h"

class FileReaderUtils {
 public:
  static std::string readFile(const std::string &filePath);

 private:
  FileReaderUtils() = default;
};
