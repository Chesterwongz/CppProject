#include "ModifiesAbstraction.h"

std::set<int> ModifiesAbstraction::getAbstractions() {
    Entity firstEntity = context.getTokenEntity(first);
    const StatementType &firstStatementType =
            EntityToStatementType.at(firstEntity);

    return pkb->getStatementsModifying(second, firstStatementType);
}