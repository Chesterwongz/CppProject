#include "PatternStorage.h"
#include "qps/common/Keywords.h"

PatternStorage::PatternStorage() = default;

void PatternStorage::setAssignPattern(const std::string& variableName, const std::string& rpn, int statementNumber) {
    variablePatternStorage[variableName].emplace_back(std::make_pair(rpn, statementNumber));
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

std::vector<std::string> PatternStorage::getExactAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym) {
    std::vector<std::string> result;
    if ((variableName == WILDCARD_KEYWORD || isSynonym) && rpn == WILDCARD_KEYWORD) {
        result = getAllStatements();
    }
    else if (variableName == WILDCARD_KEYWORD || isSynonym) {
        for (const auto& entry : statementPatternStorage) {
            if (entry.second.first == rpn) {
                result.push_back(std::to_string(entry.first));
            }
        }
    }
    else if (rpn == WILDCARD_KEYWORD) {
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

std::vector<std::string> PatternStorage::getPartialAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym) {
    std::vector<std::string> result;
    if ((variableName == WILDCARD_KEYWORD || isSynonym) && rpn == WILDCARD_KEYWORD) {
        result = getAllStatements();
    }
    else if (variableName == WILDCARD_KEYWORD || isSynonym) {
        for (const auto& entry : statementPatternStorage) {
            if (entry.second.first.find(rpn) != std::string::npos) {
                result.push_back(std::to_string(entry.first));
            }
        }
    }
    else if (rpn == WILDCARD_KEYWORD) {
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