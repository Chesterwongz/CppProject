#pragma once

#include <algorithm>
#include <memory>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/queryEvaluator/utils/tableQueue/TableQueue.h"

using std::vector, std::unique_ptr, std::reference_wrapper, std::unordered_set;

class ClauseGroup {
 private:
  TableQueue tableQueue;
  ClauseUtil::ClauseRefList clauseRefList;
  unordered_set<string> evaluatedClauses {};
  unordered_set<string> synonymsSet {};

  bool hasSelectedSynonyms(set<string>& selectedSynonyms);
  void evaluateClauseToTables(PKBReader& pkb, set<string>& selectedSynonyms);

 public:
  explicit ClauseGroup(ClauseUtil::ClauseRefList& clauseList);
  explicit ClauseGroup(unique_ptr<Clause>& clause);
  IntermediateTable evaluate(PKBReader& pkb, set<string>& selectedSynonyms);
};
