#pragma once

#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/abstraction/BaseAbstraction.h"

class AbstractionEvaluator {
public:
    static IntermediateTable evaluate(BaseAbstraction &abstraction);
};
