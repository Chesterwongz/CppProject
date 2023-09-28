#include "ModifiesAbstraction.h"

IntermediateTable ModifiesAbstraction::getAbstractions() {
    string stmtValue = firstArg.getValue();
    StmtType stmtType = firstArg.isSynonym() ?
            EntityToStatementType.at(context.getTokenEntity(stmtValue))
            : StmtType::STMT;

    // Modifies (StatementSynonym, VarSynonym)
    bool isStmtSynonymAndVarSynonym = firstArg.isSynonym() && secondArg.isSynonym();
    // Modifies (StatementSynonym, _)
    bool isStmtSynonymAndVarWildcard = firstArg.isSynonym() && secondArg.isWildcard();
    // Modifies (_, VarSynonym)
    bool isStmtWildcardAndVarSynonym = firstArg.isWildcard() && secondArg.isSynonym();
    // Modifies (_, _)
    bool isStmtWildcardAndVarWildcard = firstArg.isWildcard() && secondArg.isWildcard();
    if (isStmtSynonymAndVarSynonym
            || isStmtSynonymAndVarWildcard
            || isStmtWildcardAndVarSynonym
            || isStmtWildcardAndVarWildcard) {
        string varSynonym = secondArg.getValue();
        vector<pair<string, string>> statementsModifiedVar =
                pkb.getAllModifiedVariables(stmtType);

        return IntermediateTableFactory::buildIntermediateTable(
                stmtValue,
                varSynonym,
                statementsModifiedVar);

    }

    // Modifies (StatementSynonym, VarIdentifierInSimple)
    bool isStmtSynonymAndVarIdent = firstArg.isSynonym() && secondArg.isIdent();
    // Modifies (_, VarIdentifierInSimple)
    bool isStmtWildCardAndVarIdent = firstArg.isWildcard() && secondArg.isIdent();
    if (isStmtSynonymAndVarIdent || isStmtWildCardAndVarIdent) {
        string varIdentifier = secondArg.getValue();
        vector<string> statementsModifyingVar =
                pkb.getStatementsModifying(varIdentifier, stmtType);
        vector<string> colName = { stmtValue };
        vector<vector<string>> tableData = {};
        for (auto &stmt : statementsModifyingVar) {
            vector<string> row = { stmt };
            tableData.push_back(row);
        }
        return IntermediateTableFactory::buildIntermediateTable(
                colName,
                tableData);
    }

    // Modifies (StatementNumber, VarIdentifierInSimple)
    // Modifies (StatementNumber, VarSynonym)
    // Modifies (StatementNumber, _)
    if (firstArg.isInteger()) {
        return handleIntegerArgs(stmtValue);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable ModifiesAbstraction::handleIntegerArgs(string stmtNumber) {
    if (secondArg.isIdent() && pkb.isVariableModifiedBy(secondArg.getValue(), stmtNumber)) {
        return IntermediateTableFactory::buildWildcardIntermediateTable();
    }
    if (secondArg.isSynonym() || secondArg.isWildcard()) {
        vector<pair<string, string>> result
                = pkb.getVariablesModifiedBy(stoi(stmtNumber), StmtType::STMT);
        return IntermediateTableFactory::buildIntermediateTable(
                WILDCARD_KEYWORD,
                secondArg.getValue(),
                result);
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}


IntermediateTable ModifiesAbstraction::evaluateSynonymSynonym() {
    return handleSynonymOrWildcardArgs();
}

IntermediateTable ModifiesAbstraction::evaluateSynonymIdent() {
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgIdent = secondArg.getValue();
    vector<string> statementsModifyingVar =
            pkb.getStatementsModifying(secondArgIdent, firstArgStmtType);
    return IntermediateTableFactory::buildSingleColTable(
            firstArgValue,
            statementsModifyingVar);
}

IntermediateTable ModifiesAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}


IntermediateTable ModifiesAbstraction::evaluateIntegerSynonym() {
    int firstArgStmtNumber = stoi(this->firstArgValue);
    string secondArgVarSynonym = secondArg.getValue();
    vector<pair<string, string>> result
            = pkb.getVariablesModifiedBy(firstArgStmtNumber, StmtType::STMT);
    return IntermediateTableFactory::buildIntermediateTable(
            WILDCARD_KEYWORD,
            secondArgVarSynonym,
            result);
}

IntermediateTable ModifiesAbstraction::evaluateIntegerIdent() {
    string stmtNumber = this->firstArgValue;
    if (pkb.isVariableModifiedBy(secondArg.getValue(), stmtNumber)) {
        return IntermediateTableFactory::buildWildcardIntermediateTable();
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable ModifiesAbstraction::evaluateIntegerWildcard() {
    int firstArgStmtNumber = stoi(this->firstArgValue);
    vector<pair<string, string>> result
            = pkb.getVariablesModifiedBy(firstArgStmtNumber, StmtType::STMT);
    if (result.empty()) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return IntermediateTableFactory::buildWildcardIntermediateTable();
}


IntermediateTable ModifiesAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
}

IntermediateTable ModifiesAbstraction::evaluateWildcardIdent() {
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgIdent = secondArg.getValue();
    vector<string> statementsModifyingVar =
            pkb.getStatementsModifying(secondArgIdent, firstArgStmtType);
    return IntermediateTableFactory::buildSingleColTable(
            firstArgValue,
            statementsModifyingVar);
}

IntermediateTable ModifiesAbstraction::evaluateWildcardWildcard() {
    return handleSynonymOrWildcardArgs();
}


IntermediateTable ModifiesAbstraction::handleSynonymOrWildcardArgs() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgVarSynonym = secondArg.getValue();
    vector<pair<string, string>> statementsModifiedVar =
            pkb.getAllModifiedVariables(firstArgStmtType);
    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            firstArgStmtSynonym,
            secondArgVarSynonym,
            statementsModifiedVar);
}
