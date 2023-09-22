#include "ParentsAbstraction.h"

IntermediateTable ParentsAbstraction::getAbstractions() {
    bool isFirstStmtSynonym = firstArg.getArgumentType() == SYNONYM_TYPE;
    bool isSecondStmtSynonym = secondArg.getArgumentType() == SYNONYM_TYPE;

    string firstArgValue = firstArg.getValue();
    StmtType firstStmtType = isFirstStmtSynonym ?
                             EntityToStatementType.at(context.getTokenEntity(firstArgValue))
                                                : StmtType::STMT;
    string secondArgValue = firstArg.getValue();
    StmtType secondStmtType = isSecondStmtSynonym ?
                              EntityToStatementType.at(context.getTokenEntity(secondArgValue))
                                                  : StmtType::STMT;

    vector<pair<string, string>> statementsModifyingVar = this->isTransitive ?
            pkb.getParentChildStarPairs(firstStmtType, secondStmtType)
            : pkb.getParentChildPairs(firstStmtType, secondStmtType);

    return IntermediateTableFactory::buildIntermediateTable(
            firstArgValue,
            secondArgValue,
            statementsModifyingVar);
}
