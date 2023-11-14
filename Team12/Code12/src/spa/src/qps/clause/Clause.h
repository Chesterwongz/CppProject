#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include "BaseClause.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/clauseCache/ClauseCache.h"
#include "qps/intermediateTable/IntermediateTable.h"

typedef vector<std::unique_ptr<AbstractArgument>> ArgumentList;

using std::string, std::set, std::vector;

class Clause : public BaseClause {
 public:
  ~Clause() override = default;
  virtual vector<const AbstractArgument*> getAllArguments() = 0;
};
