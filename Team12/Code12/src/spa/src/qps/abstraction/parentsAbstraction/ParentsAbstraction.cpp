#include "ParentsAbstraction.h"

/**
  * Parents abstraction:
  * firstArg: Synonym OR Integer OR Wildcard
  * secondArg: Synonym OR Integer OR Wildcard
  */

// Parents (StmtSynonym, StmtSynonym)
IntermediateTable ParentsAbstraction::evaluateSynonymSynonym() {
    if (this->firstArgValue == this->secondArgValue) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return handleSynonymOrWildcardArgs();
}

// Parents (StmtSynonym, StmtNumber)
IntermediateTable ParentsAbstraction::evaluateSynonymInteger() {
    return handleSecondArgInteger();
}

// Parents (StmtSynonym, _)
IntermediateTable ParentsAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}

//Parents (StmtNumber, StmtSynonym)
IntermediateTable ParentsAbstraction::evaluateIntegerSynonym() {
    return handleFirstArgInteger();
}

// Parents (StmtNumber, StmtNumber)
IntermediateTable ParentsAbstraction::evaluateIntegerInteger()  {
    return handleBothArgsInteger();
}

// Parents (StmtNumber, _)
IntermediateTable ParentsAbstraction::evaluateIntegerWildcard() {
    return handleFirstArgInteger();
}

//Parents (_, StmtSynonym)
IntermediateTable ParentsAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
}

// Parents (_, StmtNumber)
IntermediateTable ParentsAbstraction::evaluateWildcardInteger()  {
    return handleSecondArgInteger();
}

// Parents (_, _)
IntermediateTable ParentsAbstraction::evaluateWildcardWildcard() {
    return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
 */
IntermediateTable ParentsAbstraction::handleSynonymOrWildcardArgs() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstStmtType = this->getFirstArgStmtType();
    string secondArgStmtSynonym = this->secondArgValue;
    StmtType secondStmtType =this->getSecondArgStmtType();

    vector<pair<string, string>> parentChildPairs = this->isTransitive
            ? pkb.getParentChildStarPairs(firstStmtType, secondStmtType)
            : pkb.getParentChildPairs(firstStmtType, secondStmtType);

    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            firstArgStmtSynonym,
            secondArgStmtSynonym,
            parentChildPairs);
}

IntermediateTable ParentsAbstraction::handleBothArgsInteger() {
    int firstArgInteger = stoi(this->firstArgValue);
    int secondArgInteger = stoi(this->secondArgValue);
    bool isValid = this->isTransitive
           ? pkb.isParentStar(firstArgInteger, secondArgInteger)
           : pkb.isParent(firstArgInteger, secondArgInteger);
    return isValid
           ? IntermediateTableFactory::buildWildcardIntermediateTable()
           : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable ParentsAbstraction::handleFirstArgInteger() {
    int firstArgInteger = stoi(this->firstArgValue);
    StmtType secondStmtType = this->getSecondArgStmtType();
    vector<pair<string, string>> results = this->isTransitive
           ? pkb.getChildrenStarOf(firstArgInteger, secondStmtType)
           : pkb.getImmediateChildrenOf(firstArgInteger, secondStmtType);
    // pass first col as wildcard so the table ignores integer column
    return IntermediateTableFactory::buildIntermediateTable(
            WILDCARD_KEYWORD,
            this->secondArgValue,
            results);
}

IntermediateTable ParentsAbstraction::handleSecondArgInteger() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = this->getFirstArgStmtType();
    int secondArgInteger = stoi(this->secondArgValue);
    vector<pair<string, string>> results;
    if (this->isTransitive) {
        results = pkb.getParentStarOf(secondArgInteger, firstArgStmtType);

    } else {
        pair<string, string> immediateParent = pkb.getImmediateParentOf(secondArgInteger, firstArgStmtType);
        if (immediateParent.first.empty() && immediateParent.second.empty()) {
            return IntermediateTableFactory::buildEmptyIntermediateTable();
        }
        vector<pair<string,string>> tmp({immediateParent});
        results = tmp;
    }
    // pass second col as wildcard so the table ignores the integer column
    return IntermediateTableFactory::buildIntermediateTable(
            firstArgStmtSynonym,
            WILDCARD_KEYWORD,
            results);
}

