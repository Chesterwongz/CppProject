#include "UsesStorage.h"

#include <iostream>
#include <map>
#include <set>

// Constructor
UsesStorage::UsesStorage() {}

// Setter and Getter for both data structures (variable -> statement numbers)
void UsesStorage::setVariableUsage(const std::string& variableName, int statementNumber) {
    variableToStatements[variableName].insert(statementNumber);
    statementToVariables[statementNumber].insert(variableName);
}

std::unordered_set<int> UsesStorage::getStatementNumbersForVariable(const std::string& variableName) {
    return variableToStatements[variableName];
}

std::unordered_set<std::string> UsesStorage::getVariablesForStatement(int statementNumber) {
    return statementToVariables[statementNumber];
}

std::set<std::string> UsesStorage::getAllVariables() {
    std::set<std::string> allVariables;
    for (const auto& entry : variableToStatements) {
        if (!entry.second.empty()) {
            allVariables.insert(entry.first); // Use insert for set
        }
    }
    return allVariables;
}

std::unordered_set<int> UsesStorage::getAllStatements() {
    std::unordered_set<int> allStatements;
    for (const auto& entry : statementToVariables) {
        if (!entry.second.empty()) {
            allStatements.insert(entry.first); // Use insert for set
        }
    }
    return allStatements;
}