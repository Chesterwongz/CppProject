#include "IAbstraction.h"

IAbstraction::IAbstraction(AbstractionParams &params) :
        pkb(params.pkb),
        context(params.context),
        abstraction(params.abstraction),
        firstArg(params.firstArg),
        secondArg(params.secondArg),
        isTransitive(params.isTransitive) {};
