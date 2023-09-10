#include "ParentsAbstraction.h"

std::set<int> ParentsAbstraction::getAbstractions() {
    Entity firstEntity = context.getTokenEntity(firstArg);
    const StatementType &firstStatementType =
            EntityToStatementType.at(firstEntity);

    Entity secondEntity = context.getTokenEntity(secondArg);
    const StatementType &secondStatementType =
            EntityToStatementType.at(secondEntity);
    // Todo:
//    return pkb->getStatementsParents(firstStatementType, secondStatementType);
};