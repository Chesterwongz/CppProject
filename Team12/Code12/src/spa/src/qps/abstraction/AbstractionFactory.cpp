#include <memory>

#include "AbstractionFactory.h"
#include "qps/abstraction/FollowsAbstraction/FollowsAbstraction.h"
#include "qps/abstraction/ModifiesAbstraction/ModifiesAbstraction.h"
#include "qps/abstraction/UsesAbstraction/UsesAbstraction.h"
#include "qps/abstraction/ParentsAbstraction/ParentsAbstraction.h"

using std::unique_ptr, std::make_unique;

unique_ptr<IAbstraction> AbstractionFactory::createAbstraction(
        struct AbstractionParams *abstractionParams) {
    AbstractionEnum abstractionEnum =
            AbstractionToEnumMap.at(abstractionParams->abstraction);
    switch (abstractionEnum) {
        case FOLLOWS_ENUM:
            return make_unique<FollowsAbstraction>(abstractionParams);
        case MODIFIES_ENUM:
            return make_unique<ModifiesAbstraction>(abstractionParams);
        case PARENTS_ENUM:
            return make_unique<ParentsAbstraction>(abstractionParams);
        case USES_ENUM:
            return make_unique<UsesAbstraction>(abstractionParams);
    }
    return nullptr;
}
