#pragma once

#include <unordered_set>
#include <vector>
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

    // Getter for each statement type
    std::unordered_set<int>& getAllReadStatements();
    std::unordered_set<int>& getAllPrintStatements();
    std::unordered_set<int>& getAllAssignStatements();
    std::unordered_set<int>& getAllCallStatements();
    std::unordered_set<int>& getAllIfStatements();
    std::unordered_set<int>& getAllWhileStatements();

private:
    std::unordered_set<int> readStmtStorage;
    std::unordered_set<int> printStmtStorage;
    std::unordered_set<int> assignStmtStorage;
    std::unordered_set<int> callStmtStorage;
    std::unordered_set<int> ifStmtStorage;
    std::unordered_set<int> whileStmtStorage;
};


