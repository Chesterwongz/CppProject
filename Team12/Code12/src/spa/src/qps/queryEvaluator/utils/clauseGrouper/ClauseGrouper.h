#pragma once

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "qps/queryEvaluator/utils/clauseGroup/ClauseGroup.h"
#include "qps/queryEvaluator/utils/clauseGroupQueue/ClauseGroupQueue.h"

using std::vector, std::unique_ptr, std::unordered_map, std::string;

class ClauseGrouper {
 private:
  static const size_t INITIAL_RANK = 0;
  static const size_t RANK_INCREMENT = 1;

  ClauseUtil::ClauseList& clauses;
  /**
   * Map element to its parent node
   */
  unordered_map<string, string> parentMap;
  /**
   * Map element to the rank of the tree it is in
   */
  unordered_map<string, size_t> rankMap;

  explicit ClauseGrouper(ClauseUtil::ClauseList& clauses);
  ClauseGroupQueue groupClauses();
  void unionSynonym(const string& syn1, const string& syn2);
  string findSynonymParent(const string& syn);

 public:
  static ClauseGroupQueue groupClauses(ClauseUtil::ClauseList& clauses);
};
