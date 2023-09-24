#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include "qps/context/Context.h"
#include "pkb/facade/PKBReader.h"
#include "qps/intermediateTable/IntermediateTable.h"

using std::string, std::set, std::map, std::pair, std::vector;

class Clause {
public:
    virtual IntermediateTable evaluate(
            Context& context,
            PKBReader& pkb) = 0;
    virtual ~Clause() = default;
    virtual bool isEquals(const Clause& other) = 0;
};