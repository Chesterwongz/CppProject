#include "ModifiesAbstraction.h"

QueryResult ModifiesAbstraction::getAbstractions() {
    QueryResult queryResult = {};

    bool isStmtSynonym = firstArg->getArgumentType() == SYNONYM_TYPE;
    bool isVarIdentifier = secondArg->getArgumentType() == IDENT_TYPE;

    // Modifies (StatementSynonym, VariableName)
    if (isStmtSynonym && isVarIdentifier) {
        string stmtSynonym = firstArg->getValue();
        const StmtType stmtType =
                EntityToStatementType.at(context.getTokenEntity(stmtSynonym));

        string varIdentifier = secondArg->getValue();
// todo:
//        set<string> statementsModifyingVar =
//                pkb->getStatementsModifying(varIdentifier, stmtType);
//
//
//        queryResult[stmtSynonym] = statementsModifyingVar;
    }

    bool isVarSynonym = secondArg->getArgumentType() == SYNONYM_TYPE;


    return queryResult;
}
