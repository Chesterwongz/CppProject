#pragma once

#include "IAbstraction.h"

class AbstractionFactory {
public:
    static IAbstraction *createAbstraction(
            struct AbstractionParams *abstractionParams);
};
