#include "ModifiesAbstraction.h"

std::set<int> ModifiesAbstraction::getAbstractions() {
    Entity firstEntity = context.getTokenEntity(firstArg);
    const StatementType &firstStatementType =
            EntityToStatementType.at(firstEntity);

    return pkb->getStatementsModifying(secondArg, firstStatementType);
}
