#include "PKBReader.h"

#include <set>

//not complete
// Method to get the names of all variables in the program
std::unordered_set<std::string>PKBReader::getAllVariables() {
    return designEntitiesStorage.getAllVariables();
}

// Method to get the values of all constants in the program
std::unordered_set<std::string> PKBReader::getAllConstants() {
    return designEntitiesStorage.getAllConstants();
}

// Method to get the names of all procedures in the program
std::unordered_set<std::string> PKBReader::getAllProcedures() {
    return designEntitiesStorage.getAllProcedures();
}

// Method to return the statement numbers of statements
std::unordered_set<int> PKBReader::getStatement(StmtType statementType) {
    if (statementType == StmtType::STMT) {
        return statementStorage.getAllStatements();
    }
    else {
        return statementStorage.getStatementNumbersFromStatementType(statementType);
    }
}


int PKBReader::getFollowing(int statementNumber, StmtType statementType) {
    int followingStatement = followsStorage.getImmediateFollows(statementNumber);
    std::unordered_set<int> allMatchingStatementTypes = statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followingStatement != -1) {
        auto it = allMatchingStatementTypes.find(followingStatement);

        if (it != allMatchingStatementTypes.end()) {
            return followingStatement;
        }
    }

    return -1;
}

std::vector<std::pair<int, int>> PKBReader::getFollowsPairs(StmtType statementType1, StmtType statementType2) {
    std::unordered_set<int> firstStatementList = statementStorage.getStatementNumbersFromStatementType(statementType1);
    std::unordered_set<int> secondStatementList = statementStorage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<int, int>> followsPairs;

    for (int firstStatement : firstStatementList) {
        int followsResult = followsStorage.getImmediateFollows(firstStatement);
        if (followsResult != -1 && secondStatementList.count(followsResult)) {
            followsPairs.emplace_back(firstStatement, followsResult);
        }
    }

    return followsPairs;
}



int PKBReader::getFollowed(int statementNumber, StmtType statementType) {
    int followedStatement = followsStorage.getImmediateFollowedBy(statementNumber);
    std::unordered_set<int> allMatchingStatementTypes = statementStorage.getStatementNumbersFromStatementType(statementType);

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
        result = modifiesStorage.getStatementNumbersForVariable(variableName);
    }
    else {
        std::unordered_set<int> allMatchingStatements = statementStorage.getStatementNumbersFromStatementType(statementType);

        for (int statement : allMatchingStatements) {
            std::unordered_set<std::string> variables = modifiesStorage.getVariablesForStatement(statement);

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
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    // Check if the statement is of the correct type
    StmtType typeOfStatement = statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables modified by the statement
        result = modifiesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::unordered_set<int> PKBReader::getStatementsUsing(const std::string& variableName, StmtType statementType) {
    std::unordered_set<int> result;

    if (statementType == StmtType::STMT) {
        result = usesStorage.getStatementNumbersForVariable(variableName);
    }
    else {
        // Get the statement numbers of the correct type
        std::unordered_set<int> statementNumbers = statementStorage.getStatementNumbersFromStatementType(statementType);

        // Iterate through the statements
        for (int statementNumber : statementNumbers) {
            // Get the variables used by the statement
            std::unordered_set<std::string> usedVariables = usesStorage.getVariablesForStatement(statementNumber);

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
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    // Check if the statement is of the correct type
    StmtType typeOfStatement = statementStorage.getStatementTypeFromStatementNumber(statementNumber);
    if (typeOfStatement == statementType) {
        // Get the variables used by the statement
        result = usesStorage.getVariablesForStatement(statementNumber);
    }

    return result;
}

std::unordered_set<int> PKBReader::getAllStatementsModifying(std::string variableName) {
    return modifiesStorage.getStatementNumbersForVariable(variableName);
}

std::unordered_set<int> PKBReader::getAllStatementsUsing(std::string variableName) {
    return usesStorage.getStatementNumbersForVariable(variableName);
}

std::unordered_set<std::string>PKBReader::getAllUsedVariables() {
    return usesStorage.getAllVariables();
}

std::unordered_set<std::string> PKBReader::getAllModifiedVariables() {
    return modifiesStorage.getAllVariables();
}

std::unordered_set<int> PKBReader::getAllUsingStatements() {
    return usesStorage.getAllStatements();
}

std::unordered_set<int> PKBReader::getAllModifyingStatements() {
    return modifiesStorage.getAllStatements();;
}
