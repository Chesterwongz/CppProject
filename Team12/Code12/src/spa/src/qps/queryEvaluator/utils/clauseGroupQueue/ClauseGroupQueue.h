#pragma once

#include <algorithm>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "qps/queryEvaluator/utils/clauseGroup/ClauseGroup.h"

using std::vector, std::unique_ptr;

class ClauseGroupQueue {
 private:
  std::queue<ClauseGroup> clauseGroupQueue;

 public:
  void addClauseGroup(const ClauseGroup& clause);
  IntermediateTable evaluate(PKBReader& pkb, set<string> selectedSynonyms);
  /**
   * for testing usage only
   */
  std::queue<ClauseGroup>& getQueue();
};
