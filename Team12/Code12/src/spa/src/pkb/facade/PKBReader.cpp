// DUMMY PKBReader
#include "PKBReader.h"

std::vector<std::string> PKBReader::getAllVariables() {
    return {};
}

std::vector<int> PKBReader::getAllConstants() {
    return {};
}

std::vector<std::string> PKBReader::getAllProcedures() {
    return {};
}

std::unordered_set<int> PKBReader::getStatement(std::string statementType) {
    return {1, 2, 3};
}

int PKBReader::getFollowing(int statementNumber, std::string statementType) {
    return 0;
}

int PKBReader::getFollowed(int statementNumber, std::string statementType) {
    return 0;
}

std::unordered_set<int> PKBReader::getStatementsModifying(std::string variableName, std::string statementType) {
    return {4,5,6};
}

std::unordered_set<std::string> PKBReader::getVariablesModifiedBy(int statementNumber, std::string statementType) {
    return {};
}

std::unordered_set<int> PKBReader::getStatementsUsing(std::string variableName, std::string statementType) {
    return {};
}

std::unordered_set<std::string> PKBReader::getVariablesUsedBy(int statementNumber, std::string statementType) {
    return {};
}

std::unordered_set<int> PKBReader::getAllStatementsModifying(std::string variableName) {
    return {};
}

std::unordered_set<int> PKBReader::getAllStatementsUsing(std::string variableName) {
    return {};
}

std::unordered_set<std::string> PKBReader::getAllUsedVariables() {
    return {};
}

std::unordered_set<std::string> PKBReader::getAllModifiedVariables() {
    return {};
}

std::unordered_set<int> PKBReader::getAllUsingStatements() {
    return {};
}

std::unordered_set<int> PKBReader::getAllModifyingStatements() {
    return {};
}



