#include "UsesAbstraction.h"

std::set<int> UsesAbstraction::getAbstractions() {
    Entity firstEntity = context.getTokenEntity(first);
    const StatementType &firstStatementType =
            EntityToStatementType.at(firstEntity);

    return pkb->getStatementsModifying(second, firstStatementType);
};