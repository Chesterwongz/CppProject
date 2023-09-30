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

    vector<pair<string, string>> followPairs
            = pkb.getFollowsPairs(firstStmtType, secondStmtType);

    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            this->firstArgValue,
            this->secondArgValue,
            followPairs);
}

IntermediateTable FollowsAbstraction::handleBothArgsInteger() {
    int firstStmtNumber = stoi(this->firstArgValue);
    int secondStmtNumber = stoi(this->secondArgValue);
    bool isValid = pkb.isFollows(firstStmtNumber, secondStmtNumber);
    return isValid
           ? IntermediateTableFactory::buildWildcardIntermediateTable()
           : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable FollowsAbstraction::handleFirstArgInteger() {
    int firstStmtNumber = stoi(this->firstArgValue);
    StmtType secondStmtType = this->getSecondArgStmtType();
    string secondStmtSynonym = this->secondArgValue;

    string followingStmt = pkb.getFollowing(firstStmtNumber, secondStmtType);

    if (followingStmt != INVALID_STATEMENT_NUMBER) {
        return IntermediateTableFactory::buildIntermediateTable(secondStmtSynonym, followingStmt);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable FollowsAbstraction::handleSecondArgInteger() {
    StmtType firstStmtType = this->getFirstArgStmtType();
    string firstStmtSynonym = this->firstArgValue;
    int secondStmtNumber = stoi(this->secondArgValue);

    string followedStmt = pkb.getFollowed(secondStmtNumber, firstStmtType);
    if (followedStmt != INVALID_STATEMENT_NUMBER) {
        return IntermediateTableFactory::buildIntermediateTable(firstStmtSynonym, followedStmt);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
}
