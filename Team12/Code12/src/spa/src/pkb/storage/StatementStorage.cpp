#include "StatementStorage.h"

// Constructor
StatementStorage::StatementStorage() = default;

// Setter for each statement type
void StatementStorage::setStatement(int statementNumber, StmtType statementType) {
    allStmtStorage[statementType].insert(statementNumber);
    allStatements.insert(statementNumber);
}

std::unordered_set<int> StatementStorage::getAllStatements() {
    return allStatements;
}

// Getter for each statement type
std::unordered_set<int> StatementStorage::getStatementNumbersFromStatementType(StmtType statementType) {
    return allStmtStorage[statementType];
}


StmtType StatementStorage::getStatementTypeFromStatementNumber(int statementNumber) {
    for (const auto& entry : allStmtStorage) {
        const std::unordered_set<int>& statementNumbers = entry.second;
        if (statementNumbers.find(statementNumber) != statementNumbers.end()) {
            return entry.first;
        }
    }
    return StmtType::INVALID;
}