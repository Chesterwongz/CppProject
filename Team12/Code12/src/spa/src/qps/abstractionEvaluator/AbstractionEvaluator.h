#pragma once

#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/abstraction/IAbstraction.h"

class AbstractionEvaluator {
public:
    static IntermediateTable evaluate(IAbstraction &abstraction);
};
