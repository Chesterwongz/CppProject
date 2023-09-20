#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class PatternStorage {
public:
    PatternStorage();

    // Setter for assignment expressions in the program
    void setPattern(std::string variableName, std::string rpn, int statementNumber);

    // Return all assignment statements
    std::vector<std::string> getAllStatements();

    // Return all assignment statements with variableName on the LHS
    std::vector<std::string> getAllStatementsWithVariable(const std::string& variableName);

    // Return all statement numbers that contain the exact match
    std::vector<std::string> getExactPattern(std::string variableName, std::string rpn);

    // Return all the statement numbers that contain a partial match
    std::vector<std::string> getPartialPattern(std::string variableName, std::string rpn);

private:
    // variableName --> (RPN, stmtNum)
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> variablePatternStorage;

    // stmtNum --> (variableName, RPN)
    std::unordered_map<int, std::pair<std::string, std::string>> statementPatternStorage;

    std::string wildcard = "_";
};