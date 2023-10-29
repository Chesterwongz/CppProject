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
  std::priority_queue<ClauseGroup> clauseGroupQueue;

 public:
  void addClauseGroup(const ClauseGroup& clause);
  IntermediateTable evaluate(PKBReader& pkb);
  /**
   * for testing usage only
   */
  std::priority_queue<ClauseGroup>& getQueue();
};

/**
 * for min heap implementation
 */
bool operator<(const ClauseGroup &thisGroup,
               const ClauseGroup &otherGroup);

