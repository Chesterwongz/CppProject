#include "ModifiesStorage.h"

#include <iostream>
#include <vector>
#include <map>

// Constructor
ModifiesStorage::ModifiesStorage() {}

// Setter and Getter for both data structures (variable -> statement numbers and statement number -> variables)
void ModifiesStorage::setVariableModification(const std::string& variableName, int statementNumber) {
    if (!variableToStatements.count(variableName)) {
        variableToStatements[variableName] = std::vector<int>{ statementNumber };
    }
    else {
        auto& statementNumbers = variableToStatements[variableName];
        auto it = std::lower_bound(statementNumbers.begin(), statementNumbers.end(), statementNumber);
        if (it == statementNumbers.end() || *it != statementNumber) {
            statementNumbers.insert(it, statementNumber);
        }
    }

    if (!statementToVariables.count(statementNumber)) {
        statementToVariables[statementNumber] = std::vector<std::string>{ variableName };
    }
    else {
        auto& variableNames = statementToVariables[statementNumber];
        if (std::find(variableNames.begin(), variableNames.end(), variableName) == variableNames.end()) {
            variableNames.push_back(variableName);
        }
    }
}

std::vector<int> ModifiesStorage::getStatementNumbersForVariable(const std::string& variableName) {
    if (variableToStatements.count(variableName)) {
        return variableToStatements[variableName];
    }
    else {
        return std::vector<int>();
    }
}

std::vector<std::string> ModifiesStorage::getVariablesForStatement(int statementNumber) {
    if (statementToVariables.count(statementNumber)) {
        return statementToVariables[statementNumber];
    }
    else {
        return std::vector<std::string>();
    }
}

std::vector<std::string> ModifiesStorage::getAllVariables() {
    std::vector<std::string> allVariables;
    for (const auto& entry : variableToStatements) {
        allVariables.push_back(entry.first);
    }
    return allVariables;
}

std::vector<int> ModifiesStorage::getAllStatements() {
    std::vector<int> allStatements;
    for (const auto& entry : statementToVariables) {
        allStatements.push_back(entry.first);
    }
    return allStatements;
}


// Data structure for the first type of relationship (variable -> statement numbers)
std::map<std::string, std::vector<int>> variableToStatements;

// Data structure for the second type of relationship (statement number -> variable names)
std::map<int, std::vector<std::string>> statementToVariables;

