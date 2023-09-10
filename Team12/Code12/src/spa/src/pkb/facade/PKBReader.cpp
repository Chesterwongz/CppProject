#include "PKBReader.h"

#include <iostream>
#include <set>
#include <map>

//not complete
PKBReader::PKBReader() {}

// Method to get the names of all variables in the program
std::vector<std::string>PKBReader::getAllVariables() {
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

// Method to return the statement numbers of statements
std::unordered_set<int> PKBReader::getStatement(std::string statementType) {
    if (statementType == "STMT") {
        return statementStorage.getAllStatements();
    }
    else {
        return statementStorage.getStatement(statementType);
    }
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

std::set<int> PKBReader::getStatementsModifying(std::string variableName, std::string statementType) {
    std::set<int> result;

    if (statementType == "STMT") {
        result = modifiesStorage.getStatementNumbersForVariable(variableName);
    }
    else {
        std::unordered_set<int> allMatchingStatements = statementStorage.getStatementNumbersFromStatementType(statementType);

        for (int statement : allMatchingStatements) {
            std::set<std::string> variables = modifiesStorage.getVariablesForStatement(statement);

            if (variables.find(variableName) != variables.end()) {
                result.insert(statement); // Use insert to add elements to the set
            }
        }
    }

    return result;
}


std::set<std::string> PKBReader::getVariablesModifiedBy(int statementNumber, std::string statementType) {

    std::set<std::string> result;

    if (statementType == "STMT") {
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    // Check if the statement is of the correct type
    std::string typeOfStatement = statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables modified by the statement
        result = modifiesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::set<int> PKBReader::getStatementsUsing(std::string variableName, std::string statementType) {
    std::set<int> result;

    if (statementType == "STMT") {
        result = usesStorage.getStatementNumbersForVariable(variableName);
    }
    else {
        // Get the statement numbers of the correct type
        std::unordered_set<int> statementNumbers = statementStorage.getStatementNumbersFromStatementType(statementType);

        // Iterate through the statements
        for (int statementNumber : statementNumbers) {
            // Get the variables used by the statement
            std::set<std::string> usedVariables = usesStorage.getVariablesForStatement(statementNumber);

            // Check if the specified variable is used by the statement
            if (usedVariables.find(variableName) != usedVariables.end()) {
                result.insert(statementNumber); // Use insert to add elements to the set
            }
        }
    }
    return result;
}


std::set<std::string> PKBReader::getVariablesUsedBy(int statementNumber, std::string statementType) {
    std::set<std::string> result;

    if (statementType == "STMT") {
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    // Check if the statement is of the correct type
    std::string typeOfStatement = statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables used by the statement
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::set<int> PKBReader::getAllStatementsModifying(std::string variableName) {
    return modifiesStorage.getStatementNumbersForVariable(variableName);
}

std::set<int> PKBReader::getAllStatementsUsing(std::string variableName) {
    return usesStorage.getStatementNumbersForVariable(variableName);
}

std::set<std::string>PKBReader::getAllUsedVariables() {
    return usesStorage.getAllVariables();
}

std::set<std::string> PKBReader::getAllModifiedVariables() {
    return modifiesStorage.getAllVariables();
}

std::set<int> PKBReader::getAllUsingStatements() {
    return usesStorage.getAllStatements();
}

std::set<int> PKBReader::getAllModifyingStatements() {
    return modifiesStorage.getAllStatements();
}










