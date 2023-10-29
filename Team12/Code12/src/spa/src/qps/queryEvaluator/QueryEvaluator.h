#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/clause/Clause.h"
#include "qps/query/Query.h"
#include "qps/queryEvaluator/utils/clauseGroup/ClauseGroup.h"
#include "qps/queryEvaluator/utils/clauseGroupQueue/ClauseGroupQueue.h"
#include "qps/queryEvaluator/utils/clauseGrouper/ClauseGrouper.h"
#include "qps/queryEvaluator/utils/tableQueue/TableQueue.h"

using std::vector, std::unique_ptr, std::string;

class QueryEvaluator {
 private:
  PKBReader& pkb;

 public:
  explicit QueryEvaluator(PKBReader& pkb);
  unordered_set<string> evaluate(unique_ptr<Query>& query);
};
