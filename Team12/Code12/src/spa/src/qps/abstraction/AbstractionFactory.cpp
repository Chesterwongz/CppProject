#include "AbstractionFactory.h"
#include "qps/abstraction/FollowsAbstraction/FollowsAbstraction.h"
#include "qps/abstraction/ModifiesAbstraction/ModifiesAbstraction.h"
#include "qps/abstraction/UsesAbstraction/UsesAbstraction.h"
#include "qps/abstraction/ParentsAbstraction/ParentsAbstraction.h"

std::unique_ptr<IAbstraction> AbstractionFactory::createAbstraction(
        struct AbstractionParams *abstractionParams) {
    AbstractionEnum abstractionEnum =
            AbstractionToEnumMap.at(abstractionParams->abstraction);
    switch (abstractionEnum) {
        case FOLLOWS_ENUM:
            return std::move(make_unique<FollowsAbstraction>(abstractionParams));
        case MODIFIES_ENUM:
            return std::move(make_unique<ModifiesAbstraction>(abstractionParams));
        case PARENTS_ENUM:
            return std::move(make_unique<ParentsAbstraction>(abstractionParams));
        case USES_ENUM:
            return std::move(make_unique<UsesAbstraction>(abstractionParams));
    }
    return nullptr;
};
