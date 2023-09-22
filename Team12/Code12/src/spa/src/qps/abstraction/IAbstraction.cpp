#include "IAbstraction.h"

IAbstraction::IAbstraction(unique_ptr<AbstractionParams> params) :
        pkb(params->pkb),
        context(params->context),
        abstraction(params->abstraction),
        firstArg(params->firstArg),
        secondArg(params->secondArg),
        isTransitive(params->isTransitive) {};
