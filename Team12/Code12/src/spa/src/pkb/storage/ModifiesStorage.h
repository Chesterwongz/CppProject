#pragma once

#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>

class ModifiesStorage {
public:
    ModifiesStorage();

    // Setter for modifies relationship
    void setVariableModification(const std::string& variableName, int statementNumber);

    void setVariableModification(const std::string& variableName, const std::string& procName);

    // Return all statements that modify the particular variable
    std::set<int> getStatementNumbersForVariable(const std::string& variableName);

    // Return all variables that are being modified by the particular statement
    std::set<std::string> getVariablesForStatement(int statementNumber);

    std::unordered_set<std::string> getVariablesForProc(const std::string& procName);

    // Return all variables that are being modified in the program
    std::set<std::string> getAllVariables();

    // Return all statements that modify a variable in the program
    std::set<int> getAllStatements();

private:
    // (variable -> statement numbers)
    std::unordered_map<std::string, std::set<int>> variableToStatements;

    // (statement number -> variable names)
    std::unordered_map<int, std::set<std::string>> statementToVariables;

    // (procedure name -> variable names)
    std::unordered_map<std::string, std::unordered_set<std::string>> procToVariables;

    // (variable name -> procedure names)
    std::unordered_map<std::string, std::unordered_set<std::string>> variableToProc;
};