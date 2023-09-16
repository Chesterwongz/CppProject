#pragma once

#include <vector>
#include <unordered_map>
#include <set>

class PatternStorage {
public:
    // Constructor
    PatternStorage();

    void setPattern(std::string variableName, std::string rpn, int statementNumber);

    std::string getPattern(std::string variableName, std::string rpn);

private:
    //map<LHS, pair(RPN, stmtNum)>
    //map<stmtNum, pair(LHS, RPN)>
       // map<RPN, pair(LHS, stmtNum)>
    std::unordered_map<std::string, std::pair<std::string, int>> variablePatternStorage;
    std::unordered_map<int, std::pair<std::string, std::string>> statementPatternStorage;
    std::unordered_map<std::string, std::pair<std::string, int>> rpnPatternStorage;
};