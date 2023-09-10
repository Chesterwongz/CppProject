#pragma once

#include <string>
#include <set>
#include "qps/query/Query.h"

class Clause {
public:
    virtual std::set<int> evaluate(
            Context context,
            PKBReader *pkb) = 0;
};
