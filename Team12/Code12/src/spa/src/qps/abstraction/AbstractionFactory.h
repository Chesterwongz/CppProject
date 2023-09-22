#pragma once

#include <memory>

#include "IAbstraction.h"

class AbstractionFactory {
public:
    static unique_ptr<IAbstraction> createAbstraction(
            unique_ptr<AbstractionParams> abstractionParams);
};
