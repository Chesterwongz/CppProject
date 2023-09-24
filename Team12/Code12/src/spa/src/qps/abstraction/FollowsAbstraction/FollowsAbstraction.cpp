#include "FollowsAbstraction.h"

 IntermediateTable FollowsAbstraction::getAbstractions() {
     string firstArgValue = firstArg.getValue();
     StmtType firstStmtType = firstArg.isSynonym() ?
                              EntityToStatementType.at(context.getTokenEntity(firstArgValue))
                                                 : StmtType::STMT;
     string secondArgValue = secondArg.getValue();
     StmtType secondStmtType = secondArg.isSynonym() ?
                              EntityToStatementType.at(context.getTokenEntity(secondArgValue))
                                                 : StmtType::STMT;

     if (firstArg.isInteger() || secondArg.isInteger()) {
         return handleIntegerArgs(firstArgValue, firstStmtType, secondArgValue, secondStmtType);
     }

     vector<pair<string, string>> followPairs = this->isTransitive ?
             pkb.getFollowsStarPairs(firstStmtType, secondStmtType)
             : pkb.getFollowsPairs(firstStmtType, secondStmtType);

     return IntermediateTableFactory::buildIntermediateTable(
             firstArgValue,
             secondArgValue,
             followPairs);
 }

IntermediateTable FollowsAbstraction::handleIntegerArgs(
        string firstArgValue, StmtType firstStmtType,
        string secondArgValue, StmtType secondStmtType) {
     if (firstArg.isInteger() && secondArg.isInteger()) {
        bool isValid = isTransitive
                ? pkb.isFollowsStar(stoi(firstArgValue), stoi(secondArgValue))
                : pkb.isFollows(stoi(firstArgValue), stoi(secondArgValue));
        return isValid
            ? IntermediateTableFactory::buildWildcardIntermediateTable()
            : IntermediateTableFactory::buildEmptyIntermediateTable();
     } else if (firstArg.isInteger()) {
         if (this->isTransitive) {
             vector<pair<string, string>> followStarPairs
                     = pkb.getFollowsStar(stoi(firstArgValue), secondStmtType);
             // pass first col as wildcard so the table ignores that column
             return IntermediateTableFactory::buildIntermediateTable(
                     WILDCARD_KEYWORD,
                     secondArgValue,
                     followStarPairs);
         } else {
             string followingStmt = pkb.getFollowing(stoi(firstArgValue), secondStmtType);
             if (followingStmt != INVALID_STATEMENT_NUMBER) {
                 vector<string> dataCol = {followingStmt};
                 return IntermediateTableFactory::buildSingleColTable(secondArgValue, dataCol);
             }
         }
     } else {
         if (this->isTransitive) {
             vector<pair<string, string>> followStarPairs
                     = pkb.getFollowedStar(stoi(secondArgValue), firstStmtType);
             // pass second col as wildcard so the table ignores that column
             return IntermediateTableFactory::buildIntermediateTable(
                     firstArgValue,
                     WILDCARD_KEYWORD,
                     followStarPairs);
         } else {
             string followedStmt = pkb.getFollowed(stoi(secondArgValue), firstStmtType);
             if (followedStmt != INVALID_STATEMENT_NUMBER) {
                 vector<string> dataCol = {followedStmt};
                 return IntermediateTableFactory::buildSingleColTable(firstArgValue, dataCol);
             }
         }
     }
     return IntermediateTableFactory::buildEmptyIntermediateTable();
}
