#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include "qps/context/Context.h"
#include "pkb/facade/PKBReader.h"

class Clause {
public:
    virtual std::unordered_set<int> evaluate(
            Context context,
            PKBReader& pkb) = 0;
};
