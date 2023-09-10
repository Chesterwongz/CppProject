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

std::set<int> ModifiesStorage::getStatementNumbersForVariable(const std::string& variableName) {
    return variableToStatements[variableName];
}

std::set<std::string> ModifiesStorage::getVariablesForStatement(int statementNumber) {
    return statementToVariables[statementNumber];
}

std::set<std::string> ModifiesStorage::getAllVariables() {
    std::set<std::string> allVariables;
    for (const auto& entry : variableToStatements) {
        allVariables.insert(entry.first);
    }
    return allVariables;
}

std::set<int> ModifiesStorage::getAllStatements() {
    std::set<int> allStatements;
    for (const auto& entry : statementToVariables) {
        allStatements.insert(entry.first);
    }
    return allStatements;
}
