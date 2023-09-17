#include "PKBReader.h"

#include <set>

std::set<std::string>PKBReader::getAllVariables() {
    return storage.designEntitiesStorage.getAllVariables();
}

std::set<std::string> PKBReader::getAllConstants() {
    return storage.designEntitiesStorage.getAllConstants();
}

std::set<std::string> PKBReader::getAllProcedures() {
    return storage.designEntitiesStorage.getAllProcedures();
}

std::set<std::string> PKBReader::getStatement(StmtType statementType) {
    std::set<std::string> result;

    std::set<int> temp = storage.statementStorage.getStatementNumbersFromStatementType(statementType);
    for (int stmt : temp) {
        result.insert(std::to_string(stmt));
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

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowsPairs(StmtType statementType1, StmtType statementType2) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType1);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<std::string, std::string>> followsPairs;

    for (int firstStatement : firstStatementList) {
        int followsResult = storage.followsStorage.getImmediateFollows(firstStatement);
        if (followsResult != -1 && secondStatementList.count(followsResult)) {
            followsPairs.emplace_back(std::to_string(firstStatement), std::to_string(followsResult));
        }
    }

    return followsPairs;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowsStar(int statementNumber, StmtType statementType) {
    std::set<int> allFollowsStar = storage.followsStorage.getAllFollows(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allFollowsStar) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::make_pair(std::to_string(statementNumber), std::to_string(stmt)));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowedStar(int statementNumber, StmtType statementType) {
    std::set<int> allFollowedStar = storage.followsStorage.getAllFollowedBy(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allFollowedStar) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::make_pair(std::to_string(stmt), std::to_string(statementNumber)));
        }
    }

    return result;

}

std::vector<std::pair<std::string, std::string>> PKBReader::getFollowsStarPairs(StmtType statementType1, StmtType statementType2) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType1);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(statementType2);

    std::vector<std::pair<std::string, std::string>> followsPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> followsResult = storage.followsStorage.getAllFollows(firstStatement);
        for (int follows : followsResult) {
            if (secondStatementList.count(follows)) {
                followsPairs.emplace_back(std::make_pair(std::to_string(firstStatement), std::to_string(follows)));
            }
        }
    }

    return followsPairs;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getImmediateChildrenOf(int statementNumber, StmtType statementType) {
    std::set<int> allImmediateChildren = storage.parentStorage.getImmediateChildren(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allImmediateChildren) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::to_string(statementNumber), std::to_string(stmt));
        }
    }

    return result;
}

std::pair<std::string, std::string> PKBReader::getImmediateParentOf(int statementNumber, StmtType statementType) {
    int immediateParent = storage.parentStorage.getImmediateParent(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::pair<std::string, std::string> result;

    if (allMatchingStatements.find(immediateParent) != allMatchingStatements.end()) {
        result = std::make_pair(std::to_string(statementNumber), std::to_string(immediateParent));
    }
    else {
        result = std::make_pair(std::to_string(statementNumber), "-1");
    }
    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getParentChildPairs(StmtType parentType, StmtType childType) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(parentType);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(childType);

    std::vector<std::pair<std::string, std::string>> parentChildPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> allChildren = storage.parentStorage.getImmediateChildren(firstStatement);
        for (int child : allChildren) {
            if (secondStatementList.find(child) != secondStatementList.end()) {
                parentChildPairs.push_back(std::make_pair(std::to_string(firstStatement), std::to_string(child)));
            }
        }
    }
    return parentChildPairs;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getChildrenStarOf(int statementNumber, StmtType statementType) {
    std::set<int> allChildren = storage.parentStorage.getAllChildren(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allChildren) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::make_pair(std::to_string(statementNumber), std::to_string(stmt)));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getParentStarOf(int statementNumber, StmtType statementType) {
    std::set<int> allParents = storage.parentStorage.getAllParents(statementNumber);

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    std::vector<std::pair<std::string, std::string>> result;

    for (int stmt : allParents) {
        if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
            result.emplace_back(std::make_pair(std::to_string(stmt), std::to_string(statementNumber)));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getParentChildStarPairs(StmtType parentType, StmtType childType) {
    std::set<int> firstStatementList = storage.statementStorage.getStatementNumbersFromStatementType(parentType);
    std::set<int> secondStatementList = storage.statementStorage.getStatementNumbersFromStatementType(childType);

    std::vector<std::pair<std::string, std::string>> parentChildStarPairs;

    for (int firstStatement : firstStatementList) {
        std::set<int> allChildren = storage.parentStorage.getAllChildren(firstStatement);
        for (int child : allChildren) {
            if (secondStatementList.find(child) != secondStatementList.end()) {
                parentChildStarPairs.emplace_back(std::make_pair(std::to_string(firstStatement), std::to_string(child)));
            }
        }
    }
    return parentChildStarPairs;
}

std::vector<std::string> PKBReader::getStatementsModifying(std::string variableName, StmtType statementType) {
    std::vector<std::string> result;

    std::set<int> allMatchingStatements = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    for (int statement : allMatchingStatements) {
        std::set<std::string> variables = storage.modifiesStorage.getVariablesForStatement(statement);

        if (variables.find(variableName) != variables.end()) {
            result.emplace_back(std::to_string(statement));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getVariablesModifiedBy(int statementNumber, StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;

    if (statementType == StmtType::STMT ||
        storage.statementStorage.getStatementTypeFromStatementNumber(statementNumber) == statementType) {

        std::set<std::string> variables = storage.modifiesStorage.getVariablesForStatement(statementNumber);

        for (std::string v : variables) {
            result.emplace_back(std::to_string(statementNumber), v);
        }
    }

    return result;
}

std::vector<std::string> PKBReader::getStatementsUsing(std::string variableName, StmtType statementType) {
    std::vector<std::string> result;

    std::set<int> statementNumbers = storage.statementStorage.getStatementNumbersFromStatementType(statementType);

    for (int statementNumber : statementNumbers) {
        std::set<std::string> usedVariables = storage.usesStorage.getVariablesForStatement(statementNumber);
        if (usedVariables.find(variableName) != usedVariables.end()) {
            result.emplace_back(std::to_string(statementNumber));
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getVariablesUsedBy(int statementNumber, StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;

    if (statementType == StmtType::STMT ||
        storage.statementStorage.getStatementTypeFromStatementNumber(statementNumber) == statementType) {

        std::set<std::string> variables = storage.usesStorage.getVariablesForStatement(statementNumber);

        for (std::string v : variables) {
            result.emplace_back(std::to_string(statementNumber), v);
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getAllModifiedVariables(StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;

    std::set<std::string> variables = storage.modifiesStorage.getAllVariables();

    for (std::string v : variables) {
        std::set<int> statementNumbers = storage.modifiesStorage.getStatementNumbersForVariable(v);
        for (int stmt : statementNumbers) {
            std::set<int> sameStatementType = storage.statementStorage.getStatementNumbersFromStatementType(statementType);
            if (sameStatementType.find(stmt) != sameStatementType.end()) {
                result.emplace_back(v, std::to_string(stmt));
            }
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::string>> PKBReader::getAllUsedVariables(StmtType statementType) {
    std::vector<std::pair<std::string, std::string>> result;
    std::set<std::string> variables = storage.usesStorage.getAllVariables();

    for (std::string v : variables) {
        std::set<int> statementNumbers = storage.usesStorage.getStatementNumbersForVariable(v);
        for (int stmt : statementNumbers) {
            std::set<int> sameStatementType = storage.statementStorage.getStatementNumbersFromStatementType(statementType);
            if (sameStatementType.find(stmt) != sameStatementType.end()) {
                result.emplace_back(v, std::to_string(stmt));
            }
        }
    }

    return result;
}

std::vector<std::string> PKBReader::getExactPattern(std::string variableName, std::string rpn) {
    return storage.patternStorage.getExactPattern(variableName, rpn);
}

std::vector<std::string> PKBReader::getPartialPattern(std::string variableName, std::string rpn) {
    return storage.patternStorage.getPartialPattern(variableName, rpn);
}
