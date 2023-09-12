#pragma once

#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <string>
#include "common/StmtTypes.h"

class StatementStorage {
public:
    // Constructor
    StatementStorage();

    // Setter for each statement type
    void setStatement(int statementNumber, StmtType statementType);

    std::unordered_set<int> getAllStatements();

    // Getter for each statement type
    std::unordered_set<int> getStatementNumbersFromStatementType(StmtType statementType);
    StmtType getStatementTypeFromStatementNumber(int statementNumber);

private:
    std::unordered_map<StmtType, std::unordered_set<int>> allStmtStorage;
    std::unordered_set<int> allStatements;
};