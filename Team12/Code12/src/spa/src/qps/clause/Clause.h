#pragma once

#include <string>
#include <vector>
#include "qps/query/Query.h"

class Clause {
public:
    virtual std::vector<int> evaluate(Context context) {};
};