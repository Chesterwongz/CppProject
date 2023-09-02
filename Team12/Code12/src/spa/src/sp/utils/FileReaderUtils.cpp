#include "FileReaderUtils.h"

std::string FileReaderUtils::readFile(const std::string &filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw SpException{"Could not read " + filePath};
    }

    std::string fileContents;
    std::string line;
    while (std::getline(file, line)) {
        fileContents += line + "\n";
    }

    file.close();

    return fileContents;
}
