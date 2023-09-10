#include "AbstractionFactory.h"

unique_ptr<IAbstraction> AbstractionFactory::createAbstraction(
        AbstractionParams *abstractionParams) {
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
}