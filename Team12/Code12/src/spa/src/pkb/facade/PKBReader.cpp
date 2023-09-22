#include "PKBReader.h"

#include <set>

// Method to get the names of all variables in the program
std::unordered_set<std::string>PKBReader::getAllVariables() {
    return storage.designEntitiesStorage.getAllVariables();
}

// Method to get the values of all constants in the program
std::unordered_set<std::string> PKBReader::getAllConstants() {
    return storage.designEntitiesStorage.getAllConstants();
}

// Method to get the names of all procedures in the program
std::unordered_set<std::string> PKBReader::getAllProcedures() {
    return storage.designEntitiesStorage.getAllProcedures();
}

// Method to return the statement numbers of statements
std::unordered_set<int> PKBReader::getStatement(StmtType statementType) {
    if (statementType == StmtType::STMT) {
        return storage.statementStorage.getAllStatements();
    }
    else {
        return storage.statementStorage.getStatementNumbersFromStatementType(statementType);
    }
}


int PKBReader::getFollowing(int statementNumber, StmtType statementType) {
    int followingStatement = storage.followsStorage.getImmediateFollows(statementNumber);
    std::unordered_set<int> allMatchingStatementTypes = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followingStatement != -1) {
        auto it = allMatchingStatementTypes.find(followingStatement);

        if (it != allMatchingStatementTypes.end()) {
            return followingStatement;
        }
    }

    return -1;
}

std::vector<std::pair<int, int>> PKBReader::getFollowsPairs(StmtType statementType1, StmtType statementType2) {
    std::unordered_set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType1);
    std::unordered_set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<int, int>> followsPairs;

    for (int firstStatement : firstStatementList) {
        int followsResult = storage.followsStorage.getImmediateFollows(firstStatement);
        if (followsResult != -1 && secondStatementList.count(followsResult)) {
            followsPairs.emplace_back(firstStatement, followsResult);
        }
    }

    return followsPairs;
}



int PKBReader::getFollowed(int statementNumber, StmtType statementType) {
    int followedStatement = storage.followsStorage.getImmediateFollowedBy(statementNumber);
    std::unordered_set<int> allMatchingStatementTypes = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followedStatement != -1) {
        auto it = allMatchingStatementTypes.find(followedStatement);

        if (it != allMatchingStatementTypes.end()) {
            return followedStatement;
        }
    }

    return -1;
}

std::unordered_set<int> PKBReader::getStatementsModifying(const std::string& variableName, StmtType statementType) {
    std::unordered_set<int> result;

    if (statementType == StmtType::STMT) {
        result = storage.modifiesStorage.getStatementNumbersForVariable(variableName);
    }
    else {
        std::unordered_set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

        for (int statement : allMatchingStatements) {
            std::unordered_set<std::string> variables = storage.modifiesStorage.getVariablesForStatement(statement);

            if (variables.find(variableName) != variables.end()) {
                result.insert(statement); // Use insert to add elements to the set
            }
        }
    }

    return result;
}


std::unordered_set<std::string> PKBReader::getVariablesModifiedBy(int statementNumber, StmtType statementType) {

    std::unordered_set<std::string> result;

    if (statementType == StmtType::STMT) {
        result = storage.usesStorage.getVariablesForStatement(statementNumber);
    }

    // Check if the statement is of the correct type
    StmtType typeOfStatement = storage.statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables modified by the statement
        result = storage.modifiesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::unordered_set<int> PKBReader::getStatementsUsing(const std::string& variableName, StmtType statementType) {
    std::unordered_set<int> result;

    if (statementType == StmtType::STMT) {
        result = storage.usesStorage.getStatementNumbersForVariable(variableName);
    }
    else {
        // Get the statement numbers of the correct type
        std::unordered_set<int> statementNumbers = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

        // Iterate through the statements
        for (int statementNumber : statementNumbers) {
            // Get the variables used by the statement
            std::unordered_set<std::string> usedVariables = storage.usesStorage.getVariablesForStatement(statementNumber);

            // Check if the specified variable is used by the statement
            if (usedVariables.find(variableName) != usedVariables.end()) {
                result.insert(statementNumber); // Use insert to add elements to the set
            }
        }
    }
    return result;
}


std::unordered_set<std::string> PKBReader::getVariablesUsedBy(int statementNumber, StmtType statementType) {
    std::unordered_set<std::string> result;

    if (statementType == StmtType::STMT) {
        result = storage.usesStorage.getVariablesForStatement(statementNumber);
    }

    // Check if the statement is of the correct type
    StmtType typeOfStatement = storage.statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables used by the statement
        result = storage.usesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::unordered_set<int> PKBReader::getAllStatementsModifying(std::string variableName) {
    return storage.modifiesStorage.getStatementNumbersForVariable(variableName);
}

std::unordered_set<int> PKBReader::getAllStatementsUsing(std::string variableName) {
    return storage.usesStorage.getStatementNumbersForVariable(variableName);
}

std::unordered_set<std::string>PKBReader::getAllUsedVariables() {
    return storage.usesStorage.getAllVariables();
}

std::unordered_set<std::string> PKBReader::getAllModifiedVariables() {
    return storage.modifiesStorage.getAllVariables();
}

std::unordered_set<int> PKBReader::getAllUsingStatements() {
    return storage.usesStorage.getAllStatements();
}

std::unordered_set<int> PKBReader::getAllModifyingStatements() {
    return storage.modifiesStorage.getAllStatements();
}
