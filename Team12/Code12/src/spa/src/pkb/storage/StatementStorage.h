#pragma once

#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include "common/StmtTypes.h"

class StatementStorage {
public:
    StatementStorage();

    // Setter for each statement type
    void setStatement(int statementNumber, StmtType statementType);

    // Return all statement numbers of the program
    std::set<int> getAllStatements();

    // Return all statements of a particular type
    std::set<int> getStatementNumbersFromStatementType(StmtType statementType);

    // Return the type of a particular statement
    StmtType getStatementTypeFromStatementNumber(int statementNumber);

private:
    std::unordered_map<StmtType, std::set<int>> statements;
};