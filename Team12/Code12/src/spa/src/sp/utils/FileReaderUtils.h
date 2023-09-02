#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "sp/exceptions/SpException.h"

class FileReaderUtils {
public:
    static std::string readFile(const std::string &filePath);
private:
    FileReaderUtils() = default;
};
