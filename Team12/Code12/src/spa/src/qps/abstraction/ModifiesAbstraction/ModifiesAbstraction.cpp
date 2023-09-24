#include "ModifiesAbstraction.h"

IntermediateTable ModifiesAbstraction::getAbstractions() {
    bool isStmtSynonym = firstArg.isSynonym();
    bool isStmtWildcard = firstArg.isWildcard();
    bool isVarIdentifier = secondArg.isIdent();
    bool isVarSynonym = secondArg.isSynonym();
    bool isVarWildcard = secondArg.isWildcard();

    string stmtValue = firstArg.getValue();
    StmtType stmtType = isStmtSynonym ?
            EntityToStatementType.at(context.getTokenEntity(stmtValue))
            : StmtType::STMT;

    // Modifies (StatementSynonym, VarSynonym)
    bool isStmtSynonymAndVarSynonym = isStmtSynonym && isVarSynonym;
    // Modifies (StatementSynonym, _)
    bool isStmtSynonymAndVarWildcard = isStmtSynonym && isVarWildcard;
    // Modifies (_, VarSynonym)
    bool isStmtWildcardAndVarSynonym = isStmtWildcard && isVarSynonym;
    // Modifies (_, _)
    bool isStmtWildcardAndVarWildcard = isStmtWildcard && isVarWildcard;
    if (isStmtSynonymAndVarSynonym
            || isStmtSynonymAndVarWildcard
            || isStmtWildcardAndVarSynonym
            || isStmtWildcardAndVarWildcard) {
        string varSynonym = secondArg.getValue();
        vector<pair<string, string>> statementsModifyingVar =
                pkb.getAllModifiedVariables(stmtType);

        return IntermediateTableFactory::buildIntermediateTable(
                stmtValue,
                varSynonym,
                statementsModifyingVar);

    }

    // Modifies (StatementSynonym, VarIdentifierInSimple)
    bool isStmtSynonymAndVarIdent = isStmtSynonym && isVarIdentifier;
    // Modifies (_, VarIdentifierInSimple)
    bool isStmtWildCardAndVarIdent = isStmtWildcard && isVarIdentifier;
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

    return IntermediateTableFactory::buildEmptyIntermediateTable();
}
