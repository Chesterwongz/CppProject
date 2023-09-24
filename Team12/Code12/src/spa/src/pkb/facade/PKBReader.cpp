#include "PKBReader.h"

#include <set>

std::set<std::string> PKBReader::getAllVariables() {
    return storage.getAllVariables();
}

std::set<std::string> PKBReader::getAllConstants() {
    return storage.getAllConstants();
}

std::set<std::string> PKBReader::getAllProcedures() {
    return storage.getAllProcedures();
}

std::set<std::string> PKBReader::getStatement(StmtType statementType) {
    std::set<std::string> result;

    std::set<int> temp = storage.getStatementNumbersFromStatementType(statementType);
    for (int stmt : temp) {
        result.insert(std::to_string(stmt));
    }
    return result;
}

std::string PKBReader::getFollowing(int statementNumber, StmtType statementType) {
    int followingStatement = storage.getImmediateFollows(statementNumber);
    if (followingStatement != -1 && storage.isStatementType(followingStatement, statementType)) {
        return std::to_string(followingStatement);
    }

    return std::to_string(-1);
}

std::string PKBReader::getFollowed(int statementNumber, StmtType statementType) {
    int followedStatement = storage.getImmediateFollowedBy(statementNumber);
    if (followedStatement != -1 && storage.isStatementType(followedStatement, statementType)) { 
        return std::to_string(followedStatement); 
    }

    return std::to_string(-1);
}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowsPairs(StmtType statementType1, StmtType statementType2) {
    std::set<int> firstStatementList = storage.getStatementNumbersFromStatementType(statementType1);
    std::set<int> secondStatementList = storage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<std::string, std::string>> followsPairs;

    for (int firstStatement : firstStatementList) {
        int followsResult = storage.getImmediateFollows(firstStatement);
        if (followsResult != -1 && secondStatementList.count(followsResult)) {
            followsPairs.emplace_back(std::to_string(firstStatement), std::to_string(followsResult));
        }
    }

    return followsPairs;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowsStar(int statementNumber, StmtType statementType) {
    std::set<int> allFollowsStar = storage.getAllFollows(statementNumber);

    std::set<int> allMatchingStatements = storage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allFollowsStar) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::to_string(statementNumber), std::to_string(stmt));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowedStar(int statementNumber, StmtType statementType) {
    std::set<int> allFollowedStar = storage.getAllFollowedBy(statementNumber);

    std::set<int> allMatchingStatements = storage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allFollowedStar) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::to_string(stmt), std::to_string(statementNumber));
        }
    }

    return result;

}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowsStarPairs(StmtType statementType1, StmtType statementType2) {
    std::set<int> firstStatementList = storage.getStatementNumbersFromStatementType(statementType1);
    std::set<int> secondStatementList = storage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<std::string, std::string>> followsPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> followsResult = storage.getAllFollows(firstStatement);
        for (int follows : followsResult) {
            if (secondStatementList.count(follows)) {
                followsPairs.emplace_back(std::to_string(firstStatement), std::to_string(follows));
            }
        }
    }

    return followsPairs;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getImmediateChildrenOf(int statementNumber, StmtType statementType) {
    std::set<int> allImmediateChildren = storage.getImmediateChildren(statementNumber);

    std::set<int> allMatchingStatements = storage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allImmediateChildren) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::to_string(statementNumber), std::to_string(stmt));
        }
    }

    return result;
}

std::pair<std::string, std::string> PKBReader::getImmediateParentOf(int statementNumber, StmtType statementType) {
    int immediateParent = storage.getImmediateParent(statementNumber);

    std::pair<std::string, std::string> result;

    if (immediateParent != -1 && storage.isStatementType(immediateParent, statementType)) {
        result = std::make_pair(std::to_string(immediateParent), std::to_string(statementNumber));
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getParentChildPairs(StmtType parentType, StmtType childType) {
    std::set<int> firstStatementList = storage.getStatementNumbersFromStatementType(parentType);
    std::set<int> secondStatementList = storage.getStatementNumbersFromStatementType(childType);

    std::vector<std::pair<std::string, std::string>> parentChildPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> allChildren = storage.getImmediateChildren(firstStatement);
        for (int child : allChildren) {
            if (secondStatementList.find(child) != secondStatementList.end()) {
                parentChildPairs.emplace_back(std::to_string(firstStatement), std::to_string(child));
            }
        }
    }
    return parentChildPairs;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getChildrenStarOf(int statementNumber, StmtType statementType) {
    std::set<int> allChildren = storage.getAllChildren(statementNumber);

    std::set<int> allMatchingStatements = storage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allChildren) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::to_string(statementNumber), std::to_string(stmt));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getParentStarOf(int statementNumber, StmtType statementType) {
    std::set<int> allParents = storage.getAllParents(statementNumber);

    std::set<int> allMatchingStatements = storage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allParents) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::to_string(stmt), std::to_string(statementNumber));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getParentChildStarPairs(StmtType parentType, StmtType childType) {
    std::set<int> firstStatementList = storage.getStatementNumbersFromStatementType(parentType);
    std::set<int> secondStatementList = storage.getStatementNumbersFromStatementType(childType);

    std::vector<std::pair<std::string, std::string>> parentChildStarPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> allChildren = storage.getAllChildren(firstStatement);
        for (int child : allChildren) {
            if (secondStatementList.find(child) != secondStatementList.end()) {
                parentChildStarPairs.emplace_back(std::to_string(firstStatement), std::to_string(child));
            }
        }
    }
    return parentChildStarPairs;
}

std::vector<std::string> PKBReader::getStatementsModifying(const std::string& variableName, StmtType statementType) {
    std::vector<std::string> result;

    std::set<int> allMatchingStatements = storage.getStatementNumbersFromStatementType(statementType);

    for (int statement : allMatchingStatements) {
        std::set<std::string> variables = storage.getModifiedVariablesForStatement(statement);

        if (variables.find(variableName) != variables.end()) {
            result.emplace_back(std::to_string(statement));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getVariablesModifiedBy(int statementNumber, StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;

    if (storage.isStatementType(statementNumber, statementType)) {

        std::set<std::string> variables = storage.getModifiedVariablesForStatement(statementNumber);

        for (const std::string& v : variables) {
            result.emplace_back(std::to_string(statementNumber), v);
        }
    }

    return result;
}

std::vector<std::string> PKBReader::getStatementsUsing(const std::string& variableName, StmtType statementType) {
    std::vector<std::string> result;

    std::set<int> statementNumbers = storage.getStatementNumbersFromStatementType(statementType);

    for (int statementNumber : statementNumbers) {
        std::set<std::string> usedVariables = storage.getUsedVariablesForStatement(statementNumber);
        if (usedVariables.find(variableName) != usedVariables.end()) {
            result.emplace_back(std::to_string(statementNumber));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getVariablesUsedBy(int statementNumber, StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;

    if (storage.isStatementType(statementNumber, statementType)) {

        std::set<std::string> variables = storage.getUsedVariablesForStatement(statementNumber);

        for (const std::string& v : variables) {
            result.emplace_back(std::to_string(statementNumber), v);
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getAllModifiedVariables(StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;

    std::set<std::string> variables = storage.getAllVariables();

    for (const std::string& v : variables) {
        std::set<int> statementNumbers = storage.getStatementNumbersForModifiedVariable(v);
      
        for (int stmt : statementNumbers) {
            std::set<int> sameStatementType = storage.getStatementNumbersFromStatementType(statementType);
            if (sameStatementType.find(stmt) != sameStatementType.end()) {
                result.emplace_back(v, std::to_string(stmt));
            }
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getAllUsedVariables(StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;
    std::set<std::string> variables = storage.getAllVariables();

    for (const std::string& v : variables) {
        std::set<int> statementNumbers = storage.getStatementNumbersForUsedVariable(v);

        for (int stmt : statementNumbers) {
            std::set<int> sameStatementType = storage.getStatementNumbersFromStatementType(statementType);
            if (sameStatementType.find(stmt) != sameStatementType.end()) {
                result.emplace_back(v, std::to_string(stmt));
            }
        }
    }

    return result;
}

std::vector<std::string> PKBReader::getExactAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym) {
    return storage.getExactAssignPattern(variableName, rpn, isSynonym);
}

std::vector<std::string> PKBReader::getPartialAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym) {
    return storage.getPartialAssignPattern(variableName, rpn, isSynonym);
}
