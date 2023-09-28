#include "UsesAbstraction.h"

/**
  * Uses abstraction:
  * firstArg: Synonym OR Integer OR Wildcard
  * secondArg: Synonym OR Identifier OR Wildcard
  */

// Uses (StatementSynonym, VarSynonym)
IntermediateTable UsesAbstraction::evaluateSynonymSynonym() {
    return handleSynonymOrWildcardArgs();
}

// Uses (StatementSynonym, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateSynonymIdent() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgIdent = this->secondArgValue;
    vector<string> statementsUsingVar =
            pkb.getStatementsUsing(secondArgIdent, firstArgStmtType);
    return IntermediateTableFactory::buildSingleColTable(
            firstArgStmtSynonym,
            statementsUsingVar);
}

// Uses (StatementSynonym, _)
IntermediateTable UsesAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}

// Uses (StatementNumber, VarSynonym)
IntermediateTable UsesAbstraction::evaluateIntegerSynonym() {
    int firstArgStmtNumber = stoi(this->firstArgValue);
    string secondArgVarSynonym = this->secondArgValue;
    vector<pair<string, string>> result
            = pkb.getVariablesUsedBy(firstArgStmtNumber, StmtType::STMT);
    return IntermediateTableFactory::buildIntermediateTable(
            WILDCARD_KEYWORD,
            secondArgVarSynonym,
            result);
}

// Uses (StatementNumber, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateIntegerIdent() {
    string firstArgStmtNumber = this->firstArgValue;
    string secondArgIdent = this->secondArgValue;
    if (pkb.isVariableUsedBy(secondArgIdent, firstArgStmtNumber)) {
        return IntermediateTableFactory::buildWildcardIntermediateTable();
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Uses (StatementNumber, _)
IntermediateTable UsesAbstraction::evaluateIntegerWildcard() {
    int firstArgStmtNumber = stoi(this->firstArgValue);
    vector<pair<string, string>> result
            = pkb.getVariablesUsedBy(firstArgStmtNumber, StmtType::STMT);
    if (result.empty()) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return IntermediateTableFactory::buildWildcardIntermediateTable();
}

// Uses (_, VarSynonym)
IntermediateTable UsesAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
}

// Uses (_, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateWildcardIdent() {
    string firstStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgIdent = this->secondArgValue;
    vector<string> statementsUsingVar =
            pkb.getStatementsUsing(secondArgIdent, firstArgStmtType);
    if (statementsUsingVar.empty()) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return IntermediateTableFactory::buildWildcardIntermediateTable();
}

// Uses (_, _)
IntermediateTable UsesAbstraction::evaluateWildcardWildcard() {
    return handleSynonymOrWildcardArgs();
}

IntermediateTable UsesAbstraction::handleSynonymOrWildcardArgs() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgVarSynonym = this->secondArgValue;
    vector<pair<string, string>> allStatementsUsingAllVar =
            pkb.getAllUsedVariables(firstArgStmtType);
    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            firstArgStmtSynonym,
            secondArgVarSynonym,
            allStatementsUsingAllVar);
}
