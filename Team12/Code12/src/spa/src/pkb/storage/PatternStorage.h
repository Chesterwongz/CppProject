#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class PatternStorage {
public:
    PatternStorage();

    // Setter for assignment expressions in the program
    void setAssignPattern(std::string variableName, std::string rpn, int statementNumber);

    // Return all assignment statements
    std::vector<std::string> getAllStatements();

    // Return all assignment statements with variableName on the LHS
    std::vector<std::string> getAllStatementsWithVariable(const std::string& variableName);

    // Return all statement numbers that contain the exact match
    std::vector<std::string> getExactAssignPattern(std::string variableName, std::string rpn, bool isSynonym);

    // Return all the statement numbers that contain a partial match
    std::vector<std::string> getPartialAssignPattern(std::string variableName, std::string rpn, bool isSynonym);

private:
    // variableName --> (RPN, stmtNum)
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> variablePatternStorage;

    // stmtNum --> (RPN, variableName)
    std::unordered_map<int, std::pair<std::string, std::string>> statementPatternStorage;

    std::string wildcard = "_";
};