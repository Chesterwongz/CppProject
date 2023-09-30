#include "FollowsStarAbstraction.h"

 /**
  * Follows Star abstraction:
  * firstArg: Synonym OR Integer OR Wildcard
  * secondArg: Synonym OR Integer OR Wildcard
  */

// Follows (StmtSynonym, StmtSynonym)
IntermediateTable FollowsStarAbstraction::evaluateSynonymSynonym() {
    if (this->firstArgValue == this->secondArgValue) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return handleSynonymOrWildcardArgs();
}

// Follows (StmtSynonym, StmtNumber)
IntermediateTable FollowsStarAbstraction::evaluateSynonymInteger() {
     return handleSecondArgInteger();
}

// Follows (StmtSynonym, _)
IntermediateTable FollowsStarAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}

//Follows (StmtNumber, StmtSynonym)
IntermediateTable FollowsStarAbstraction::evaluateIntegerSynonym() {
    return handleFirstArgInteger();
}

// Follows (StmtNumber, StmtNumber)
IntermediateTable FollowsStarAbstraction::evaluateIntegerInteger()  {
    return handleBothArgsInteger();
}

// Follows (StmtNumber, _)
IntermediateTable FollowsStarAbstraction::evaluateIntegerWildcard() {
    return handleFirstArgInteger();
}

//Follows (StmtNumber, StmtSynonym)
IntermediateTable FollowsStarAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
 }

// Follows (_, StmtNumber)
IntermediateTable FollowsStarAbstraction::evaluateWildcardInteger()  {
    return handleSecondArgInteger();
 }

// Follows (_, _)
IntermediateTable FollowsStarAbstraction::evaluateWildcardWildcard() {
    return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
 */
IntermediateTable FollowsStarAbstraction::handleSynonymOrWildcardArgs() {
    StmtType firstStmtType = this->getFirstArgStmtType();
    StmtType secondStmtType =this->getSecondArgStmtType();

    vector<pair<string, string>> followPairs
            = pkb.getFollowsStarPairs(firstStmtType, secondStmtType);

    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            this->firstArgValue,
            this->secondArgValue,
            followPairs);
}

IntermediateTable FollowsStarAbstraction::handleBothArgsInteger() {
    int firstArgInteger = stoi(this->firstArgValue);
    int secondArgInteger = stoi(this->secondArgValue);
    bool isValid = pkb.isFollowsStar(firstArgInteger, secondArgInteger);
    return isValid
           ? IntermediateTableFactory::buildWildcardIntermediateTable()
           : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable FollowsStarAbstraction::handleFirstArgInteger() {
    int firstArgInteger = stoi(this->firstArgValue);
    StmtType secondStmtType = this->getSecondArgStmtType();

    vector<pair<string, string>> followStarPairs
            = pkb.getFollowsStar(firstArgInteger, secondStmtType);
    // pass first col as wildcard so the table ignores integer column
    return IntermediateTableFactory::buildIntermediateTable(
            WILDCARD_KEYWORD,
            this->secondArgValue,
            followStarPairs);
}

IntermediateTable FollowsStarAbstraction::handleSecondArgInteger() {
    StmtType firstArgStmtType = this->getFirstArgStmtType();
    int secondArgInteger = stoi(this->secondArgValue);

    vector<pair<string, string>> followedStarPairs
            = pkb.getFollowedStar(secondArgInteger, firstArgStmtType);

    // pass second col as wildcard so the table ignores integer column
    return IntermediateTableFactory::buildIntermediateTable(
            this->firstArgValue,
            WILDCARD_KEYWORD,
            followedStarPairs);
}
