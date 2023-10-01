#pragma once
#include <string>
#include <vector>

class IPatternReader {
public:
    virtual std::vector<std::string> getExactAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym) = 0;
    virtual std::vector<std::string> getPartialAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym) = 0;
};
