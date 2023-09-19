#include "UsesAbstraction.h"

IntermediateTable UsesAbstraction::getAbstractions() {
    bool isStmtSynonym = firstArg.getArgumentType() == SYNONYM_TYPE;
    bool isStmtWildcard = firstArg.getArgumentType() == WILDCARD_TYPE;
    bool isVarIdentifier = secondArg.getArgumentType() == IDENT_TYPE;
    bool isVarSynonym = secondArg.getArgumentType() == SYNONYM_TYPE;
    bool isVarWildcard = secondArg.getArgumentType() == WILDCARD_TYPE;

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
                = pkb->getAllUsedVariables(stmtType);
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
        vector<vector<string>> statementsUsingVar =
                { pkb->getStatementsUsing(varIdentifier, stmtType) };
        vector<string> colName = { stmtValue };
        return IntermediateTableFactory::buildIntermediateTable(
                    colName,
                    statementsUsingVar);
    }

    return IntermediateTableFactory::buildEmptyIntermediateTable();
};
