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

    // Uses (StatementSynonym, VarIdentifierInSimple)
    bool isStmtSynonymAndVarIdent = firstArg.isSynonym() && secondArg.isIdent();
    // Uses (_, VarIdentifierInSimple)
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

    // Uses (StatementNumber, VarIdentifierInSimple)
    // Uses (StatementNumber, VarSynonym)
    // Uses (StatementNumber, _)
    if (firstArg.isInteger()) {
        return handleIntegerArgs(stmtValue);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
};

IntermediateTable UsesAbstraction::handleIntegerArgs(string stmtNumber) {
    if (secondArg.isIdent() && pkb.isVariableUseBy(secondArg.getValue(), stmtNumber)) {
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
