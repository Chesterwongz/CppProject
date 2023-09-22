#include "ModifiesAbstraction.h"

IntermediateTable ModifiesAbstraction::getAbstractions() {
    bool isStmtSynonym = firstArg.getArgumentType() == SYNONYM_TYPE;
    bool isStmtWildcard = firstArg.getArgumentType() == WILDCARD_TYPE;
    bool isVarIdentifier = secondArg.getArgumentType() == IDENT_TYPE;
    bool isVarSynonym = secondArg.getArgumentType() == SYNONYM_TYPE;
    bool isVarWildcard = secondArg.getArgumentType() == WILDCARD_TYPE;

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
        vector<vector<string>> statementsModifyingVar =
                { pkb.getStatementsModifying(varIdentifier, stmtType) };
        vector<string> colName = { stmtValue };
        return IntermediateTableFactory::buildIntermediateTable(
                colName,
                statementsModifyingVar);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
}
