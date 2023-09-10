#pragma once

#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <string>

class StatementStorage {
public:
    // Constructor
    StatementStorage();

    // Setter for each statement type
    void setReadStatement(int statementNumber);
    void setPrintStatement(int statementNumber);
    void setAssignStatement(int statementNumber);
    void setCallStatement(int statementNumber);
    void setIfStatement(int statementNumber);
    void setWhileStatement(int statementNumber);

    std::unordered_set<int> getAllStatements();

    // Getter for each statement type
    std::unordered_set<int> getStatement(std::string statementType);
    std::unordered_set<int> getStatementNumbersFromStatementType(std::string statementType);
    std::string getStatementTypeFromStatementNumber(int statementNumber);

private:
    std::unordered_map<std::string, std::unordered_set<int>> allStmtStorage;
};