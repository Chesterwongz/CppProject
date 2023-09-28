#include "UsesAbstraction.h"

IntermediateTable UsesAbstraction::getAbstractions() {
    string stmtValue = firstArg.getValue();
    StmtType stmtType = firstArg.isSynonym() ?
                        EntityToStatementType.at(context.getTokenEntity(stmtValue))
                                      : StmtType::STMT;

    // Uses (StatementSynonym, VarSynonym)
    bool isStmtSynonymAndVarSynonym = firstArg.isSynonym() && secondArg.isSynonym();
    // Uses (StatementSynonym, _)
    bool isStmtSynonymAndVarWildcard = firstArg.isSynonym() && secondArg.isWildcard();
    // Uses (_, VarSynonym)
    bool isStmtWildcardAndVarSynonym = firstArg.isWildcard() && secondArg.isSynonym();
    // Uses (_, _)
    bool isStmtWildcardAndVarWildcard = firstArg.isWildcard() && secondArg.isWildcard();
    if (isStmtSynonymAndVarSynonym
        || isStmtSynonymAndVarWildcard
        || isStmtWildcardAndVarSynonym
        || isStmtWildcardAndVarWildcard) {
        string varSynonym = secondArg.getValue();
        vector<pair<string, string>> allStatementsUsingAllVar
                = pkb.getAllUsedVariables(stmtType);
        return IntermediateTableFactory::buildIntermediateTable(
                    stmtValue,
                    varSynonym,
                    allStatementsUsingAllVar);
    }

    // Uses (StatementSynonym, VarIdentifier)
    bool isStmtSynonymAndVarIdent = firstArg.isSynonym() && secondArg.isIdent();
    // Uses (_, VarIdentifier)
    bool isStmtWildCardAndVarIdent = firstArg.isWildcard() && secondArg.isIdent();
    if (isStmtSynonymAndVarIdent || isStmtWildCardAndVarIdent) {
        string varIdentifier = secondArg.getValue();
        vector<string> statementsUsingVar =
                pkb.getStatementsUsing(varIdentifier, stmtType);
        vector<string> colName = { stmtValue };
        vector<vector<string>> tableData = {};
        for (auto &stmt : statementsUsingVar) {
            vector<string> row = { stmt };
            tableData.push_back(row);
        }
        return IntermediateTableFactory::buildIntermediateTable(
                    colName,
                    tableData);
    }

    // Uses (StatementNumber, VarIdentifier)
    // Uses (StatementNumber, VarSynonym)
    // Uses (StatementNumber, _)
    if (firstArg.isInteger()) {
        return handleIntegerArgs(stmtValue);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
};

IntermediateTable UsesAbstraction::handleIntegerArgs(string stmtNumber) {
    if (secondArg.isIdent() && pkb.isVariableUsedBy(secondArg.getValue(), stmtNumber)) {
        return IntermediateTableFactory::buildWildcardIntermediateTable();
    }
    if (secondArg.isSynonym() || secondArg.isWildcard()) {
        vector<pair<string, string>> result
                = pkb.getVariablesUsedBy(stoi(stmtNumber), StmtType::STMT);
        return IntermediateTableFactory::buildIntermediateTable(
                WILDCARD_KEYWORD,
                secondArg.getValue(),
                result);
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

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
