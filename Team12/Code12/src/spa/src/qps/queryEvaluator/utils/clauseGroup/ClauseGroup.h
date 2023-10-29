#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "qps/queryEvaluator/utils/tableQueue/TableQueue.h"

using std::vector, std::unique_ptr, std::reference_wrapper;

class ClauseGroup {
 private:
  TableQueue tableQueue;
  ClauseUtil::ClauseRefList clauseRefList;
  int score{};

  void evaluateClauseToTables(PKBReader& pkb);

 public:
  explicit ClauseGroup(ClauseUtil::ClauseRefList& clauseList);
  explicit ClauseGroup(unique_ptr<Clause>& clause);
  IntermediateTable evaluate(PKBReader& pkb);
};
