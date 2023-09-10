#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <string>

class UsesStorage {
public:
    // Constructor
    UsesStorage();

    // Setter and Getter for the first data structure (variable -> statement numbers)
    void setVariableUsage(const std::string& variableName, int statementNumber);
    std::set<int> getStatementNumbersForVariable(const std::string& variableName);
    std::set<std::string> getVariablesForStatement(int statementNumber);

    // Additional methods
    std::set<std::string> getAllVariables();
    std::set<int> getAllStatements();

private:
    // Data structure for the first type of relationship (variable -> statement numbers)
    std::unordered_map<std::string, std::set<int>> variableToStatements;

    // Data structure for the second type of relationship (statement number -> variable names)
    std::unordered_map<int, std::set<std::string>> statementToVariables;
};