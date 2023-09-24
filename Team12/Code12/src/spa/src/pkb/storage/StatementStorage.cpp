#include "StatementStorage.h"

StatementStorage::StatementStorage() = default;

void StatementStorage::setStatement(int statementNumber, StmtType statementType) {
    statements[statementType].insert(statementNumber);
}

std::set<int> StatementStorage::getAllStatements() {
    std::set<int> allStatements;

    for (const auto& entry : statements) {
        const std::set<int>& statementSet = entry.second;
        allStatements.insert(statementSet.begin(), statementSet.end());
    }

    return allStatements;
}

std::set<int> StatementStorage::getStatementNumbersFromStatementType(StmtType statementType) {
    if (statementType == StmtType::STMT) {
        return getAllStatements();
    }
    return statements[statementType];
}

StmtType StatementStorage::getStatementTypeFromStatementNumber(int statementNumber) {
    for (const auto& entry : statements) {
        const std::set<int>& statementNumbers = entry.second;
        if (statementNumbers.find(statementNumber) != statementNumbers.end()) {
            return entry.first;
        }
    }
    return StmtType::INVALID;
}

bool StatementStorage::isStatementType(int statementNumber, StmtType statementType) {
    return statementType == StmtType::STMT || getStatementTypeFromStatementNumber(statementNumber) == statementType;
}