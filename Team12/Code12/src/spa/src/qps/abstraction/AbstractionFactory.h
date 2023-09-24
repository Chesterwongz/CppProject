#pragma once

#include <memory>

#include "IAbstraction.h"

class AbstractionFactory {
public:
    static unique_ptr<IAbstraction> createAbstraction(
            AbstractionParams &abstractionParams);
};
