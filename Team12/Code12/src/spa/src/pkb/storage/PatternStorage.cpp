#include "PatternStorage.h"
#include "../../common/Types.h"

#include <iostream>
#include <vector>

// Constructor
PatternStorage::PatternStorage() = default;

void PatternStorage::setPattern(std::string variableName, std::string rpn, int statementNumber) {
    variablePatternStorage[variableName].insert(std::make_pair(rpn, statementNumber));
    statementPatternStorage[statementNumber] = std::make_pair(rpn, variableName);
}

std::vector<std::string> PatternStorage::getAllStatements() {
    std::vector<std::string> result;
    for (const auto& entry : statementPatternStorage) {
        result.push_back(std::to_string(entry.first));
    }
    return result;
}

std::vector<std::string> PatternStorage::getAllStatementsWithVariable(const std::string& variableName) {
    std::vector<std::string> result;

    auto it = variablePatternStorage.find(variableName);
    if (it != variablePatternStorage.end()) {
        for (const auto& pair : it->second) {
            result.push_back(std::to_string(pair.second));
        }
    }

    return result;
}

std::vector<std::string> PatternStorage::getExactPattern(std::string variableName, std::string rpn) {
    std::vector<std::string> result;
    if (variableName == wildcard && rpn == wildcard) {
        result = getAllStatements();
    }
    else if (variableName == wildcard) {
        for (const auto& entry : statementPatternStorage) {
            if (entry.second.second == rpn) {
                result.push_back(std::to_string(entry.first));
            }
        }
    }
    else if (rpn == wildcard) {
        result = getAllStatementsWithVariable(variableName);
    }
    else {
        for (const auto& entry : statementPatternStorage) {
            if (entry.second.first == rpn && entry.second.second == variableName) {
                result.push_back(std::to_string(entry.first));
            }
        }
    }
    return result;
}

std::vector<std::string> PatternStorage::getPartialPattern(std::string variableName, std::string rpn) {
    std::vector<std::string> result;
    if (variableName == wildcard && rpn == wildcard) {
        result = getAllStatements();
    }
    else if (variableName == wildcard) {
        for (const auto& entry : statementPatternStorage) {
            if (entry.second.second.find(rpn) != std::string::npos) {
                result.push_back(std::to_string(entry.first));
            }
        }
    }
    else if (rpn == wildcard) {
        result = getAllStatementsWithVariable(variableName);
    }
    else {
        for (const auto& entry : statementPatternStorage) {
            if (entry.second.first.find(rpn) != std::string::npos && entry.second.second == variableName) {
                result.push_back(std::to_string(entry.first));
            }
        }
    }
    return result;
}





