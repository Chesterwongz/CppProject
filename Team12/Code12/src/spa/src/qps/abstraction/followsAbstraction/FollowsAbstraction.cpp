#include "FollowsAbstraction.h"

 /**
  * Follows abstraction:
  * firstArg: Synonym OR Integer OR Wildcard
  * secondArg: Synonym OR Integer OR Wildcard
  */

 IntermediateTable FollowsAbstraction::getAbstractions() {
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

// Follows (Synonym, Synonym)
IntermediateTable FollowsAbstraction::evaluateSynonymSynonym() {
    if (this->firstArgValue == this->secondArgValue) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return handleNoArgsInteger();
}

// Follows (Synonym, Integer)
IntermediateTable FollowsAbstraction::evaluateSynonymInteger() {
     return handleSecondArgInteger();
}

// Follows (Synonym, _)
IntermediateTable FollowsAbstraction::evaluateSynonymWildcard() {
    return handleNoArgsInteger();
}

//Follows (Integer, Synonym)
IntermediateTable FollowsAbstraction::evaluateIntegerSynonym() {
    return handleFirstArgInteger();
}

// Follows (Integer, Integer)
IntermediateTable FollowsAbstraction::evaluateIntegerInteger()  {
    return handleBothArgsInteger();
}

// Follows (Integer, _)
IntermediateTable FollowsAbstraction::evaluateIntegerWildcard() {
    return handleFirstArgInteger();
}

//Follows (Integer, Synonym)
IntermediateTable FollowsAbstraction::evaluateWildcardSynonym() {
    return handleNoArgsInteger();
 }

// Follows (Integer, Integer)
IntermediateTable FollowsAbstraction::evaluateWildcardInteger()  {
    return handleSecondArgInteger();
 }

// Follows (_, _)
IntermediateTable FollowsAbstraction::evaluateWildcardWildcard() {
    return handleNoArgsInteger();
}

/**
 * For handling cases where both args are non-integer
 */
IntermediateTable FollowsAbstraction::handleNoArgsInteger() {
    StmtType firstStmtType = this->getFirstArgStmtType();
    StmtType secondStmtType =this->getSecondArgStmtType();

    vector<pair<string, string>> followPairs = this->isTransitive
           ? pkb.getFollowsStarPairs(firstStmtType, secondStmtType)
           : pkb.getFollowsPairs(firstStmtType, secondStmtType);

    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            this->firstArgValue,
            this->secondArgValue,
            followPairs);
}

IntermediateTable FollowsAbstraction::handleBothArgsInteger() {
    int firstArgInteger = stoi(firstArgValue);
    int secondArgInteger = stoi(secondArgValue);
    bool isValid = isTransitive
                   ? pkb.isFollowsStar(firstArgInteger, secondArgInteger)
                   : pkb.isFollows(firstArgInteger, secondArgInteger);
    return isValid
           ? IntermediateTableFactory::buildWildcardIntermediateTable()
           : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable FollowsAbstraction::handleFirstArgInteger() {
    int firstArgInteger = stoi(this->firstArgValue);
    StmtType secondStmtType = this->getSecondArgStmtType();
    if (this->isTransitive) {
        vector<pair<string, string>> followStarPairs
                = pkb.getFollowsStar(firstArgInteger, secondStmtType);
        // pass first col as wildcard so the table ignores integer column
        return IntermediateTableFactory::buildIntermediateTable(
                WILDCARD_KEYWORD,
                this->secondArgValue,
                followStarPairs);
    } else {
        string followingStmt = pkb.getFollowing(firstArgInteger, secondStmtType);
        if (followingStmt != INVALID_STATEMENT_NUMBER) {
            return IntermediateTableFactory::buildIntermediateTable(this->secondArgValue, followingStmt);
        }
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable FollowsAbstraction::handleSecondArgInteger() {
    StmtType firstArgStmtType = this->getFirstArgStmtType();
    int secondArgInteger = stoi(this->secondArgValue);
    if (this->isTransitive) {
        vector<pair<string, string>> followedStarPairs
                = pkb.getFollowedStar(secondArgInteger, firstArgStmtType);
        // pass second col as wildcard so the table ignores integer column
        return IntermediateTableFactory::buildIntermediateTable(
                this->firstArgValue,
                WILDCARD_KEYWORD,
                followedStarPairs);
    } else {
        string followedStmt = pkb.getFollowed(secondArgInteger, firstArgStmtType);
        if (followedStmt != INVALID_STATEMENT_NUMBER) {
            return IntermediateTableFactory::buildIntermediateTable(this->firstArgValue, followedStmt);
        }
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}
