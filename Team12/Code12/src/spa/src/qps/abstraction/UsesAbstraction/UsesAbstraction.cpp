#include "UsesAbstraction.h"

std::set<int> UsesAbstraction::getAbstractions() {
    Entity firstEntity = context.getTokenEntity(firstArg);
    const StatementType &firstStatementType =
            EntityToStatementType.at(firstEntity);

    return pkb->getStatementsModifying(secondArg, firstStatementType);
};
