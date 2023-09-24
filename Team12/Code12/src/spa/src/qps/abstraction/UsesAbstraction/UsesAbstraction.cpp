#include "UsesAbstraction.h"

IntermediateTable UsesAbstraction::getAbstractions() {
    bool isStmtSynonym = firstArg.isSynonym();
    bool isStmtWildcard = firstArg.isWildcard();
    bool isVarIdentifier = secondArg.isIdent();
    bool isVarSynonym = secondArg.isSynonym();
    bool isVarWildcard = secondArg.isWildcard();

    string stmtValue = firstArg.getValue();
    StmtType stmtType = isStmtSynonym ?
                        EntityToStatementType.at(context.getTokenEntity(stmtValue))
                                      : StmtType::STMT;

    // Uses (StatementSynonym, VarSynonym)
    bool isStmtSynonymAndVarSynonym = isStmtSynonym && isVarSynonym;
    // Uses (StatementSynonym, _)
    bool isStmtSynonymAndVarWildcard = isStmtSynonym && isVarWildcard;
    // Uses (_, VarSynonym)
    bool isStmtWildcardAndVarSynonym = isStmtWildcard && isVarSynonym;
    // Uses (_, _)
    bool isStmtWildcardAndVarWildcard = isStmtWildcard && isVarWildcard;
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
    bool isStmtSynonymAndVarIdent = isStmtSynonym && isVarIdentifier;
    // Uses (_, VarIdentifierInSimple)
    bool isStmtWildCardAndVarIdent = isStmtWildcard && isVarIdentifier;
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

    return IntermediateTableFactory::buildEmptyIntermediateTable();
};
