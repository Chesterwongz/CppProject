# include "StatementStorage.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

// Constructor
StatementStorage::StatementStorage() {}

// Setter
void StatementStorage::setStatement(const std::string& statementType, int statementNumber) {
    if (!statementStorage.count(statementType)) {
        statementStorage[statementType] = std::vector<int>{ statementNumber };
    }
    else {
        auto& statementNumbers = statementStorage[statementType];
        auto it = std::lower_bound(statementNumbers.begin(), statementNumbers.end(), statementNumber);
        if (it == statementNumbers.end() || *it != statementNumber) {
            statementNumbers.insert(it, statementNumber);
        }
    }
}

// First Getter
std::vector<int> StatementStorage::getStatementNumbersFromStatementType(const std::string& statementType) {
    if (statementStorage.count(statementType)) {
        return statementStorage[statementType];
    }
    else {
        return std::vector<int>();
    }
}

// Second Getter
std::vector<std::string> StatementStorage::getStatementTypesFromStatementNumber(int statementNumber) {
    std::vector<std::string> statements;
    for (const auto& entry : statementStorage) {
        if (std::binary_search(entry.second.begin(), entry.second.end(), statementNumber)) {
            statements.push_back(entry.first);
        }
    }
    return statements;
}

// Data structure for statement storage (statement type -> line numbers)
std::map<std::string, std::vector<int>> statementStorage;
