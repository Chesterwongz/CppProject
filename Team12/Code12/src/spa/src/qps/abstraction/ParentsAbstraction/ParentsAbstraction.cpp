#include "ParentsAbstraction.h"

IntermediateTable ParentsAbstraction::getAbstractions() {
    string firstArgValue = firstArg.getValue();
    StmtType firstStmtType = firstArg.isSynonym() ?
                             EntityToStatementType.at(context.getTokenEntity(firstArgValue))
                                                : StmtType::STMT;
    string secondArgValue = secondArg.getValue();
    StmtType secondStmtType = secondArg.isSynonym() ?
                              EntityToStatementType.at(context.getTokenEntity(secondArgValue))
                                                  : StmtType::STMT;

    if (firstArgValue != WILDCARD_KEYWORD && (firstArgValue == secondArgValue)) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }

    if (firstArg.isInteger() || secondArg.isInteger()) {
        return handleIntegerArgs(firstArgValue, firstStmtType, secondArgValue, secondStmtType);
    }

    vector<pair<string, string>> parentChildPairs = this->isTransitive ?
            pkb.getParentChildStarPairs(firstStmtType, secondStmtType)
            : pkb.getParentChildPairs(firstStmtType, secondStmtType);

    return IntermediateTableFactory::buildIntermediateTable(
            firstArgValue,
            secondArgValue,
            parentChildPairs);
}

IntermediateTable ParentsAbstraction::handleIntegerArgs(
        string firstArgValue, StmtType firstStmtType,
        string secondArgValue, StmtType secondStmtType) {
    if (firstArg.isInteger() && secondArg.isInteger()) {
        bool isValid = isTransitive
                       ? pkb.isParentStar(stoi(firstArgValue), stoi(secondArgValue))
                       : pkb.isParent(stoi(firstArgValue), stoi(secondArgValue));
        return isValid
               ? IntermediateTableFactory::buildWildcardIntermediateTable()
               : IntermediateTableFactory::buildEmptyIntermediateTable();
    } else if (firstArg.isInteger()) {
        vector<pair<string, string>> results = this->isTransitive
                ? pkb.getChildrenStarOf(stoi(firstArgValue), secondStmtType)
                : pkb.getImmediateChildrenOf(stoi(firstArgValue), secondStmtType);
        // pass first col as wildcard so the table ignores that column
        return IntermediateTableFactory::buildIntermediateTable(
                WILDCARD_KEYWORD,
                secondArgValue,
                results);
    } else {
        vector<pair<string, string>> results;
        if (this->isTransitive) {
            results = pkb.getParentStarOf(stoi(secondArgValue), firstStmtType);
        } else {
            pair<string, string> immediateParent = pkb.getImmediateParentOf(stoi(secondArgValue), firstStmtType);
            if (immediateParent.first.empty() && immediateParent.second.empty()) {
                return IntermediateTableFactory::buildEmptyIntermediateTable();
            }
            vector<pair<string,string>> tmp({immediateParent});
            results = tmp;
        }
        // pass second col as wildcard so the table ignores that column
        return IntermediateTableFactory::buildIntermediateTable(
                firstArgValue,
                WILDCARD_KEYWORD,
                results);
    }
}
