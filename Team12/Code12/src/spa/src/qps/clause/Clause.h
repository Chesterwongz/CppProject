#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include <memory>
#include <vector>
#include "qps/context/Context.h"
#include "pkb/facade/PKBReader.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/argument/AbstractArgument.h"

typedef vector<std::unique_ptr<AbstractArgument>> ArgumentList;

using std::string, std::set, std::map, std::pair, std::vector;

class Clause {
public:
    virtual IntermediateTable evaluate(
            Context& context,
            PKBReader& pkb) = 0;
    virtual ~Clause() = default;
    virtual bool isEquals(const Clause& other) = 0;
};
