#include "StatementStorage.h"

// Constructor
StatementStorage::StatementStorage() = default;

// Setter for each statement type
void StatementStorage::setStatement(int statementNumber, StmtType statementType) {
    allStmtStorage[statementType].insert(statementNumber);
    allStatements.insert(statementNumber);
}

std::set<int> StatementStorage::getAllStatements() {
    return allStatements;
}

// Getter for each statement type
std::set<int> StatementStorage::getStatementNumbersFromStatementType(StmtType statementType) {
    if (statementType == StmtType::STMT) {
        return allStatements;
    }
    return allStmtStorage[statementType];
}


StmtType StatementStorage::getStatementTypeFromStatementNumber(int statementNumber) {
    for (const auto& entry : allStmtStorage) {
        const std::set<int>& statementNumbers = entry.second;
        if (statementNumbers.find(statementNumber) != statementNumbers.end()) {
            return entry.first;
        }
    }
    return StmtType::INVALID;
}