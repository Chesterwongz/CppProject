#include "PKBReader.h"

#include <iostream>
#include <vector>
#include <map>

//not complete
PKBReader::PKBReader() {}

// Method to get the names of all variables in the program
std::vector<std::string> PKBReader::getAllVariables() {
    return designEntitiesStorage.getAllVariables();
}

// Method to get the values of all constants in the program
std::vector<int> PKBReader::getAllConstants() {
    return designEntitiesStorage.getAllConstants();
}

// Method to get the names of all procedures in the program
std::vector<std::string> PKBReader::getAllProcedures() {
    return designEntitiesStorage.getAllProcedures();
}

std::unordered_set<int> PKBReader::getAllStmts() {
    return statementStorage.getAllStatements();
}

// Method to return the statement numbers of all READ statements
std::unordered_set<int> PKBReader::getAllRead() {
    return statementStorage.getAllReadStatements();
}

// Method to return the statement numbers of all PRINT statements
std::unordered_set<int> PKBReader::getAllPrint() {
    return statementStorage.getAllPrintStatements();
}

// Method to return the statement numbers of all ASSIGN statements
std::unordered_set<int> PKBReader::getAllAssign() {
    return statementStorage.getAllAssignStatements();
}

// Method to return the statement numbers of all CALL statements
std::unordered_set<int> PKBReader::getAllCall() {
    return statementStorage.getAllCallStatements();
}

// Method to return the statement numbers of all WHILE statements
std::unordered_set<int> PKBReader::getAllWhile() {
    return statementStorage.getAllWhileStatements();
}

// Method to return the statement numbers of all IF statements
std::unordered_set<int> PKBReader::getAllIf() {
    return statementStorage.getAllIfStatements();
}

int PKBReader::getFollowing(int statementNumber, std::string statementType) {
    int followingStatement = followsStorage.getImmediateFollows(statementNumber);
    std::unordered_set<int> allMatchingStatementTypes = statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followingStatement != -1) {
        auto it = std::find(allMatchingStatementTypes.begin(), allMatchingStatementTypes.end(), followingStatement);

        if (it != allMatchingStatementTypes.end()) {
            return followingStatement;
        }
    }

    return -1;
}


int PKBReader::getFollowed(int statementNumber, std::string statementType) {
    int followedStatement = followsStorage.getImmediateFollowedBy(statementNumber);
    std::unordered_set<int> allMatchingStatementTypes = statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followedStatement != -1) {
        auto it = std::find(allMatchingStatementTypes.begin(), allMatchingStatementTypes.end(), followedStatement);

        if (it != allMatchingStatementTypes.end()) {
            return followedStatement;
        }
    }

    return -1;
}

std::vector<int> PKBReader::getStatementsModifying(std::string variableName, std::string statementType) {
    std::unordered_set<int> allMatchingStatements = statementStorage.getStatementNumbersFromStatementType(statementType);
    std::vector<int> result;

    for (int statement : allMatchingStatements) {
        std::vector<std::string> variables = modifiesStorage.getVariablesForStatement(statement);

        if (std::find(variables.begin(), variables.end(), variableName) != variables.end()) {
            result.push_back(statement);
        }
    }

    return result;
}

std::vector<std::string> PKBReader::getVariablesModifiedBy(int statementNumber, std::string statementType) {
    std::vector<std::string> result;

    // Check if the statement is of the correct type
    std::string typeOfStatement = statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables modified by the statement
        result = modifiesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::vector<int> PKBReader::getStatementsUsing(std::string variableName, std::string statementType) {
    std::vector<int> result;

    // Get the statement numbers of the correct type
    std::unordered_set<int> statementNumbers = statementStorage.getStatementNumbersFromStatementType(statementType);

    // Iterate through the statements
    for (int statementNumber : statementNumbers) {
        // Get the variables used by the statement
        std::vector<std::string> usedVariables = usesStorage.getVariablesForStatement(statementNumber);

        // Check if the specified variable is used by the statement
        if (std::find(usedVariables.begin(), usedVariables.end(), variableName) != usedVariables.end()) {
            result.push_back(statementNumber);
        }
    }

    return result;
}

std::vector<std::string> PKBReader::getVariablesUsedBy(int statementNumber, std::string statementType) {
    std::vector<std::string> result;

    // Check if the statement is of the correct type
    std::string typeOfStatement = statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables used by the statement
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}





