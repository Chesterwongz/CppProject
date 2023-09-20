#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include "qps/context/Context.h"
#include "pkb/facade/PKBReader.h"
#include "qps/clause/utils/ClauseConstants.h"

enum Reference {
    WILDCARD,
    SYNONYM,
    STRING,
    LINE_NUMBER
};

class Clause {
public:
    virtual std::unordered_set<int> evaluate(
            Context context,
            PKBReader& pkb) = 0;
};
