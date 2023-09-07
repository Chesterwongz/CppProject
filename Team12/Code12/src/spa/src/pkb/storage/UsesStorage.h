#ifndef USES_STORAGE_H
#define USES_STORAGE_H

#include <vector>
#include <map>
#include <string>

class UsesStorage {
public:
    // Constructor
    UsesStorage();

    // Setter and Getter for the first data structure (variable -> statement numbers)
    void setVariableUsage(const std::string& variableName, int statementNumber);
    std::vector<int> getStatementNumbersForVariable(const std::string& variableName);

    // Setter and Getter for the second data structure (statement number -> variable names)
    void addStatementUsage(int statementNumber, const std::string& variableName);
    std::vector<std::string> getVariablesForStatement(int statementNumber);

    // Additional methods
    std::vector<std::string> getAllVariables();
    std::vector<int> getAllStatements();

private:
    // Data structure for the first type of relationship (variable -> statement numbers)
    std::map<std::string, std::vector<int>> variableToStatements;

    // Data structure for the second type of relationship (statement number -> variable names)
    std::map<int, std::vector<std::string>> statementToVariables;
};

#endif // USES_STORAGE_H
