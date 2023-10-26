#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../intermediateTable/IntermediateTableFactory.h"
#include "pkb/facade/PKBReader.h"
#include "qps/clause/Clause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/query/Query.h"

using std::vector, std::unique_ptr, std::string;

typedef vector<unique_ptr<Clause>> ClauseList;

class QueryEvaluator {
 private:
  PKBReader& pkb;
  std::priority_queue<IntermediateTable> tableQueue;
  IntermediateTable getJoinResult();

 public:
  explicit QueryEvaluator(PKBReader& pkb);
  unordered_set<string> evaluate(unique_ptr<Query>& query);
};
