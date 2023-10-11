#include "PatternReader.h"

std::vector<std::pair<std::string, std::string>>
PatternReader::getExactAssignPattern(const std::string& variableName,
                                     const std::string& rpn) {
  return pattern_storage_.getExactAssignPattern(variableName, rpn);
}

std::vector<std::pair<std::string, std::string>>
PatternReader::getPartialAssignPattern(const std::string& variableName,
                                       const std::string& rpn) {
  return pattern_storage_.getPartialAssignPattern(variableName, rpn);
}

std::vector<std::pair<std::string, std::string>> PatternReader::getWhilePattern(
    const std::string& variableName) {
  return pattern_storage_.getWhilePattern(variableName);
}

std::vector<std::pair<std::string, std::string>> PatternReader::getIfPattern(
    const std::string& variableName) {
  return pattern_storage_.getIfPattern(variableName);
}
