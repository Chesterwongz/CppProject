#pragma once

#include "IAbstraction.h"
//#include "qps/clause/utils/ClauseConstants.h"
//#include "FollowsAbstraction/FollowsAbstraction.h"
//#include "ModifiesAbstraction/ModifiesAbstraction.h"
//#include "ParentsAbstraction/ParentsAbstraction.h"
//#include "UsesAbstraction/UsesAbstraction.h"

class AbstractionFactory {
public:
    static IAbstraction *createAbstraction(
            struct AbstractionParams *abstractionParams);
};

