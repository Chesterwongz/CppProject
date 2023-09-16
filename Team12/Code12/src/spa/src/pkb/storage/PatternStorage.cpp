#include "PatternStorage.h"

#include <iostream>
#include <vector>

// Constructor
PatternStorage::PatternStorage() = default;

void PatternStorage::setPattern(std::string variableName, std::string rpn, int statementNumber) {
    variablePatternStorage[variableName] = std::make_pair(rpn, statementNumber);
    statementPatternStorage[statementNumber] = std::make_pair(rpn, variableName);
    rpnPatternStorage[rpn] = std::make_pair(variableName, statementNumber);
}

std::string PatternStorage::getPattern(std::string variableName, std::string rpn) {
    return "hello";
}

