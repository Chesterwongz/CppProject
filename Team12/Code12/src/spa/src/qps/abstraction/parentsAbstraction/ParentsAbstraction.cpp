#include "ParentsAbstraction.h"

/**
  * Parents abstraction:
  * firstArg: Synonym OR Integer OR Wildcard
  * secondArg: Synonym OR Integer OR Wildcard
  */

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
        // pass second col as wildcard so the table ignores the integer column
        return IntermediateTableFactory::buildIntermediateTable(
                firstArgValue,
                WILDCARD_KEYWORD,
                results);
    }
}


// Parents (Synonym, Synonym)
IntermediateTable ParentsAbstraction::evaluateSynonymSynonym() {
    if (this->firstArgValue == this->secondArgValue) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return handleSynonymOrWildcardArgs();
}

// Parents (Synonym, Integer)
IntermediateTable ParentsAbstraction::evaluateSynonymInteger() {
    return handleSecondArgInteger();
}

// Parents (Synonym, _)
IntermediateTable ParentsAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}

//Parents (Integer, Synonym)
IntermediateTable ParentsAbstraction::evaluateIntegerSynonym() {
    return handleFirstArgInteger();
}

// Parents (Integer, Integer)
IntermediateTable ParentsAbstraction::evaluateIntegerInteger()  {
    return handleBothArgsInteger();
}

// Parents (Integer, _)
IntermediateTable ParentsAbstraction::evaluateIntegerWildcard() {
    return handleFirstArgInteger();
}

//Parents (Integer, Synonym)
IntermediateTable ParentsAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
}

// Parents (Integer, Integer)
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

