#include "PKBReader.h"

#include <set>

// Method to get the names of all variables in the program
std::set<std::string>PKBReader::getAllVariables() {
    return storage.designEntitiesStorage.getAllVariables();
}

// Method to get the values of all constants in the program
std::set<std::string> PKBReader::getAllConstants() {
    return storage.designEntitiesStorage.getAllConstants();
}

// Method to get the names of all procedures in the program
std::set<std::string> PKBReader::getAllProcedures() {
    return storage.designEntitiesStorage.getAllProcedures();
}

// Method to return the statement numbers of statements
std::set<std::string> PKBReader::getStatement(StmtType statementType) {
    std::set<std::string> result;

    std::set<int> temp = storage.statementStorage.getStatementNumbersFromStatementType(statementType);
    for (int stmt : temp) {
        result.insert(std::to_string(stmt)); // Convert int to string
    }
    return result;
}


std::string PKBReader::getFollowing(int statementNumber, StmtType statementType) {
    int followingStatement = storage.followsStorage.getImmediateFollows(statementNumber);
    std::set<int> allMatchingStatementTypes = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followingStatement != -1) {
        auto it = allMatchingStatementTypes.find(followingStatement);

        if (it != allMatchingStatementTypes.end()) {
            return std::to_string(followingStatement);
        }
    }

    return std::to_string(-1);
}

std::string PKBReader::getFollowed(int statementNumber, StmtType statementType) {
    int followedStatement = storage.followsStorage.getImmediateFollowedBy(statementNumber);
    std::set<int> allMatchingStatementTypes = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    if (followedStatement != -1) {
        auto it = allMatchingStatementTypes.find(followedStatement);

        if (it != allMatchingStatementTypes.end()) {
            return std::to_string(followedStatement);
        }
    }

    return std::to_string(-1);
}

std::vector<std::pair<int, int>> PKBReader::getFollowsPairs(StmtType statementType1, StmtType statementType2) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType1);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<int, int>> followsPairs;

    for (int firstStatement : firstStatementList) {
        int followsResult = storage.followsStorage.getImmediateFollows(firstStatement);
        if (followsResult != -1 && secondStatementList.count(followsResult)) {
            followsPairs.emplace_back(firstStatement, followsResult);
        }
    }

    return followsPairs;
}

std::set<std::string> PKBReader::getFollowsStar(int statementNumber, StmtType statementType) {
    std::set<int> allFollowsStar = storage.followsStorage.getAllFollows(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::set<std::string> result;
    // Iterate through the result set
    for (int stmt : allFollowsStar) {
        // If the statement is also present in allMatchingStatements, add it to the common set
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.insert(std::to_string(stmt));
        }
    }

    return result;
}

std::set<std::string> PKBReader::getFollowedStar(int statementNumber, StmtType statementType) {
    std::set<int> allFollowedStar = storage.followsStorage.getAllFollowedBy(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::set<std::string> result;
    // Iterate through the result set
    for (int stmt : allFollowedStar) {
        // If the statement is also present in allMatchingStatements, add it to the common set
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.insert(std::to_string(stmt));
        }
    }

    return result;

}

//
std::set<std::string> PKBReader::getImmediateChildrenOf(int statementNumber, StmtType statementType) {
    std::set<int> allImmediateChildren = storage.parentStorage.getImmediateChildren(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::set<std::string> result;
    // Iterate through the result set
    for (int stmt : allImmediateChildren) {
        // If the statement is also present in allMatchingStatements, add it to the common set
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.insert(std::to_string(stmt));
        }
    }

    return result;
}

std::string PKBReader::getImmediateParentOf(int statementNumber, StmtType statementType) {
    int immediateParent = storage.parentStorage.getImmediateParent(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    if (allMatchingStatements.find(immediateParent) != allMatchingStatements.end()) {
        return std::to_string(immediateParent);
    }
    else {
        return std::to_string(-1);
    }
}

std::vector<std::pair<int, int>> PKBReader::getParentChildPairs(StmtType parentType, StmtType childType) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(parentType);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(childType);

    std::vector<std::pair<int, int>> parentChildPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> allChildren = storage.parentStorage.getImmediateChildren(firstStatement);
        for (int child : allChildren) {
            if (secondStatementList.find(child) != secondStatementList.end()) {
                parentChildPairs.push_back(std::make_pair(firstStatement, child));
            }
        }
    }
    return parentChildPairs;
}

std::set<std::string> PKBReader::getParentStarOf(int statementNumber, StmtType statementType) {
    std::set<int> allParents = storage.parentStorage.getAllParents(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::set<std::string> result;

    for (int stmt : allParents) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.insert(std::to_string(stmt));
        }
    }

    return result;
}

std::set<std::string> PKBReader::getChildrenStarOf(int statementNumber, StmtType statementType) {
    std::set<int> allChildren = storage.parentStorage.getAllChildren(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::set<std::string> result;

    for (int stmt : allChildren) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.insert(std::to_string(stmt));
        }
    }

    return result;
}



std::vector<std::pair<int, int>> PKBReader::getParentChildStarPairs(StmtType parentType, StmtType childType) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(parentType);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(childType);

    std::vector<std::pair<int, int>> parentChildStarPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> allChildren = storage.parentStorage.getAllChildren(firstStatement);
        for (int child : allChildren) {
            if (secondStatementList.find(child) != secondStatementList.end()) {
                parentChildStarPairs.push_back(std::make_pair(firstStatement, child));
            }
        }
    }
    return parentChildStarPairs;
}

std::set<std::string> PKBReader::getStatementsModifying(const std::string& variableName, StmtType statementType) {
    std::set<std::string> result;

    if (statementType == StmtType::STMT) {
        std::set<int>  statementNumbers = storage.modifiesStorage.getStatementNumbersForVariable(variableName);
        for (int stmt : statementNumbers) {
            result.insert(std::to_string(stmt)); // Convert int to string
        }
    }
    else {
        std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

        for (int statement : allMatchingStatements) {
            std::set<std::string> variables = storage.modifiesStorage.getVariablesForStatement(statement);

            if (variables.find(variableName) != variables.end()) {
                result.insert(std::to_string(statement)); // Use insert to add elements to the set
            }
        }
    }

    return result;
}


std::set<std::string> PKBReader::getVariablesModifiedBy(int statementNumber, StmtType statementType) {

    std::set<std::string> result;

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

std::set<std::string> PKBReader::getStatementsUsing(const std::string& variableName, StmtType statementType) {
    std::set<std::string> result;

    if (statementType == StmtType::STMT) {
        std::set<int> statementNumbers = storage.usesStorage.getStatementNumbersForVariable(variableName);
        for (int stmt : statementNumbers) {
            result.insert(std::to_string(stmt)); // Convert int to string
        }
    }
    else {
        // Get the statement numbers of the correct type
        std::set<int> statementNumbers = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

        // Iterate through the statements
        for (int statementNumber : statementNumbers) {
            // Get the variables used by the statement
            std::set<std::string> usedVariables = storage.usesStorage.getVariablesForStatement(statementNumber);

            // Check if the specified variable is used by the statement
            if (usedVariables.find(variableName) != usedVariables.end()) {
                result.insert(std::to_string(statementNumber)); // Convert int to string
            }
        }
    }
    return result;
}



std::set<std::string> PKBReader::getVariablesUsedBy(int statementNumber, StmtType statementType) {
    std::set<std::string> result;

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

std::set<int> PKBReader::getAllStatementsModifying(std::string variableName) {
    return storage.modifiesStorage.getStatementNumbersForVariable(variableName);
}

std::set<int> PKBReader::getAllStatementsUsing(std::string variableName) {
    return storage.usesStorage.getStatementNumbersForVariable(variableName);
}

std::set<std::string>PKBReader::getAllUsedVariables(StmtType statementType) {
    return storage.usesStorage.getAllVariables();
}

std::set<std::string> PKBReader::getAllModifiedVariables(StmtType statementType) {

    return storage.modifiesStorage.getAllVariables();
}

std::set<std::string> PKBReader::getAllUsingStatements(StmtType statementType) {
    std::set<std::string> result;

    std::set<int> allUsingStatements = storage.usesStorage.getAllStatements();

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    for (int stmt : allMatchingStatements) {
        if (allUsingStatements.find(stmt) != allUsingStatements.end()) {
            result.insert(std::to_string(stmt));
        }
    }

    return result;
}

std::set<std::string> PKBReader::getAllModifyingStatements(StmtType statementType) {
    std::set<std::string> result;

    std::set<int> allModifyingStatements = storage.modifiesStorage.getAllStatements();

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    for (int stmt : allMatchingStatements) {
        if (allModifyingStatements.find(stmt) != allModifyingStatements.end()) {
            result.insert(std::to_string(stmt)); // Convert int to string
        }
    }
    return result;
}

