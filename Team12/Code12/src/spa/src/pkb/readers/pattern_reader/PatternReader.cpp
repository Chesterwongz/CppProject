#include "PatternReader.h"

std::vector<std::pair<std::string, std::string>>
PatternReader::getExactAssignPattern(const std::string& variableName,
                                     const std::string& rpn, bool isSynonym) {
  return pattern_storage_.getExactAssignPattern(variableName, rpn, isSynonym);
}

std::vector<std::pair<std::string, std::string>>
PatternReader::getPartialAssignPattern(const std::string& variableName,
                                       const std::string& rpn, bool isSynonym) {
  return pattern_storage_.getPartialAssignPattern(variableName, rpn, isSynonym);
}
