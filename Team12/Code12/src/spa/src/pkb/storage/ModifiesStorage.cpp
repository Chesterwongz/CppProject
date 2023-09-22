#include "ModifiesStorage.h"

#include <iostream>
#include <set>
#include <map>

// Constructor
ModifiesStorage::ModifiesStorage() {}

// Setter and Getter for both data structures (variable -> statement numbers and statement number -> variables)
void ModifiesStorage::setVariableModification(const std::string& variableName, int statementNumber) {
    variableToStatements[variableName].insert(statementNumber);
    statementToVariables[statementNumber].insert(variableName);
}

std::unordered_set<int> ModifiesStorage::getStatementNumbersForVariable(const std::string& variableName) {
    if (variableToStatements.find(variableName) == variableToStatements.end()) {
        return {};
    }
    return variableToStatements[variableName];
}

std::unordered_set<std::string> ModifiesStorage::getVariablesForStatement(int statementNumber) {
    if (statementToVariables.find(statementNumber) == statementToVariables.end()) {
        return {};
    }
    return statementToVariables[statementNumber];
}

std::unordered_set<std::string> ModifiesStorage::getAllVariables() {
    std::unordered_set<std::string> allVariables;
    for (const auto& entry : variableToStatements) {
        allVariables.insert(entry.first); // Use insert for set
    }
    return allVariables;
}

std::unordered_set<int> ModifiesStorage::getAllStatements() {
    std::unordered_set<int> allStatements;
    for (const auto& entry : statementToVariables) {
        allStatements.insert(entry.first); // Use insert for set
    }
    return allStatements;}