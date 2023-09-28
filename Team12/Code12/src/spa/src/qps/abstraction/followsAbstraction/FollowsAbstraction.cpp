#include "FollowsAbstraction.h"

 /**
  * Follows abstraction:
  * firstArg: Synonym OR Integer OR Wildcard
  * secondArg: Synonym OR Integer OR Wildcard
  */

// Follows (StmtSynonym, StmtSynonym)
IntermediateTable FollowsAbstraction::evaluateSynonymSynonym() {
    if (this->firstArgValue == this->secondArgValue) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return handleSynonymOrWildcardArgs();
}

// Follows (StmtSynonym, StmtNumber)
IntermediateTable FollowsAbstraction::evaluateSynonymInteger() {
     return handleSecondArgInteger();
}

// Follows (StmtSynonym, _)
IntermediateTable FollowsAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}

//Follows (StmtNumber, StmtSynonym)
IntermediateTable FollowsAbstraction::evaluateIntegerSynonym() {
    return handleFirstArgInteger();
}

// Follows (StmtNumber, StmtNumber)
IntermediateTable FollowsAbstraction::evaluateIntegerInteger()  {
    return handleBothArgsInteger();
}

// Follows (StmtNumber, _)
IntermediateTable FollowsAbstraction::evaluateIntegerWildcard() {
    return handleFirstArgInteger();
}

//Follows (StmtNumber, StmtSynonym)
IntermediateTable FollowsAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
 }

// Follows (_, StmtNumber)
IntermediateTable FollowsAbstraction::evaluateWildcardInteger()  {
    return handleSecondArgInteger();
 }

// Follows (_, _)
IntermediateTable FollowsAbstraction::evaluateWildcardWildcard() {
    return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
 */
IntermediateTable FollowsAbstraction::handleSynonymOrWildcardArgs() {
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
    int firstArgInteger = stoi(this->firstArgValue);
    int secondArgInteger = stoi(this->secondArgValue);
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
