#include "AbstractionFactory.h"
#include "qps/abstraction/FollowsAbstraction/FollowsAbstraction.h"
#include "qps/abstraction/ModifiesAbstraction/ModifiesAbstraction.h"
#include "qps/abstraction/UsesAbstraction/UsesAbstraction.h"
#include "qps/abstraction/ParentsAbstraction/ParentsAbstraction.h"

IAbstraction *AbstractionFactory::createAbstraction(
        struct AbstractionParams *abstractionParams) {
    AbstractionEnum abstractionEnum =
            AbstractionToEnumMap.at(abstractionParams->abstraction);
    switch (abstractionEnum) {
        case FOLLOWS_ENUM:
            return make_shared<FollowsAbstraction>(abstractionParams).get();
        case MODIFIES_ENUM:
            return make_shared<ModifiesAbstraction>(abstractionParams).get();
        case PARENTS_ENUM:
            return make_shared<ParentsAbstraction>(abstractionParams).get();
        case USES_ENUM:
            return make_shared<UsesAbstraction>(abstractionParams).get();
    }
    return nullptr;
}