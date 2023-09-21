#pragma once

#include <set>
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

    std::set<int> getAllStatements();

    // Getter for each statement type
    std::set<int> getStatementNumbersFromStatementType(StmtType statementType);
    StmtType getStatementTypeFromStatementNumber(int statementNumber);

private:
    std::unordered_map<StmtType, std::set<int>> allStmtStorage;
    std::set<int> allStatements;
};