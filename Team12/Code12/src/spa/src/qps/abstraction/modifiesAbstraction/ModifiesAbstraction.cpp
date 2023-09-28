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

    // Modifies (StatementSynonym, VarIdentifier)
    bool isStmtSynonymAndVarIdent = firstArg.isSynonym() && secondArg.isIdent();
    // Modifies (_, VarIdentifier)
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

    // Modifies (StatementNumber, VarIdentifier)
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
                this->secondArgValue,
                result);
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Modifies (StatementSynonym, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateSynonymSynonym() {
    return handleSynonymOrWildcardArgs();
}

// Modifies (StatementSynonym, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateSynonymIdent() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgIdent = this->secondArgValue;
    vector<string> statementsModifyingVar =
            pkb.getStatementsModifying(secondArgIdent, firstArgStmtType);
    return IntermediateTableFactory::buildSingleColTable(
            firstArgStmtSynonym,
            statementsModifyingVar);
}

// Modifies (StatementSynonym, _)
IntermediateTable ModifiesAbstraction::evaluateSynonymWildcard() {
    return handleSynonymOrWildcardArgs();
}

// Modifies (StatementNumber, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateIntegerSynonym() {
    int firstArgStmtNumber = stoi(this->firstArgValue);
    string secondArgVarSynonym = this->secondArgValue;
    vector<pair<string, string>> result
            = pkb.getVariablesModifiedBy(firstArgStmtNumber, StmtType::STMT);
    return IntermediateTableFactory::buildIntermediateTable(
            WILDCARD_KEYWORD,
            secondArgVarSynonym,
            result);
}

// Modifies (StatementNumber, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateIntegerIdent() {
    string stmtNumber = this->firstArgValue;
    if (pkb.isVariableModifiedBy(this->secondArgValue,
                                 stmtNumber)) {
        return IntermediateTableFactory::buildWildcardIntermediateTable();
    }
    return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Modifies (StatementNumber, _)
IntermediateTable ModifiesAbstraction::evaluateIntegerWildcard() {
    int firstArgStmtNumber = stoi(this->firstArgValue);
    vector<pair<string, string>> result
            = pkb.getVariablesModifiedBy(firstArgStmtNumber, StmtType::STMT);
    if (result.empty()) {
        return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    return IntermediateTableFactory::buildWildcardIntermediateTable();
}

// Modifies (_, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateWildcardSynonym() {
    return handleSynonymOrWildcardArgs();
}

// Modifies (_, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateWildcardIdent() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgIdent = this->secondArgValue;
    vector<string> statementsModifyingVar =
            pkb.getStatementsModifying(secondArgIdent, firstArgStmtType);
    return IntermediateTableFactory::buildSingleColTable(
            firstArgStmtSynonym,
            statementsModifyingVar);
}

// Modifies (_, _)
IntermediateTable ModifiesAbstraction::evaluateWildcardWildcard() {
    return handleSynonymOrWildcardArgs();
}

IntermediateTable ModifiesAbstraction::handleSynonymOrWildcardArgs() {
    string firstArgStmtSynonym = this->firstArgValue;
    StmtType firstArgStmtType = getFirstArgStmtType();
    string secondArgVarSynonym = this->secondArgValue;
    vector<pair<string, string>> statementsModifiedVar =
            pkb.getAllModifiedVariables(firstArgStmtType);
    //! If any of the args are "_", the column will be ignored.
    return IntermediateTableFactory::buildIntermediateTable(
            firstArgStmtSynonym,
            secondArgVarSynonym,
            statementsModifiedVar);
}
