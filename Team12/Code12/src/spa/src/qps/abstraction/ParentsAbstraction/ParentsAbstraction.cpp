#include "ParentsAbstraction.h"

std::set<int> ParentsAbstraction::getAbstractions() {
    Entity firstEntity = context.getTokenEntity(first);
    const StatementType &firstStatementType =
            EntityToStatementType.at(firstEntity);

    Entity secondEntity = context.getTokenEntity(second);
    const StatementType &secondStatementType =
            EntityToStatementType.at(secondEntity);
    // Todo:
//    return pkb->getStatementsParents(firstStatementType, secondStatementType);
};