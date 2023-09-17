#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

class PatternStorage {
public:
    // Constructor
    PatternStorage();

    void setPattern(std::string variableName, std::string rpn, int statementNumber);

    std::vector<std::string> getAllStatements();

    std::vector<std::string> getAllStatementsWithVariable(const std::string& variableName);

    std::vector<std::string> getExactPattern(std::string variableName, std::string rpn);

    std::vector<std::string> getPartialPattern(std::string variableName, std::string rpn);

private:
    //map<variableName, pair(RPN, stmtNum)>
    std::unordered_map<std::string, std::unordered_set<std::pair<std::string, int>>> variablePatternStorage;

    //map<stmtNum, pair(variableName, RPN)>
    std::unordered_map<int, std::pair<std::string, std::string>> statementPatternStorage;
};