#pragma once

#include <memory>

#include "IAbstraction.h"

class AbstractionFactory {
public:
    static std::unique_ptr<IAbstraction> createAbstraction(
            struct AbstractionParams &abstractionParams);
};
