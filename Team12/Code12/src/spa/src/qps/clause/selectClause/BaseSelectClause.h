#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/BaseClause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

class BaseSelectClause : public BaseClause {
 protected:
  SynonymsToSelect synonymsToSelect;
  set<string> synonymsInOtherClauses;
  bool isDisableCaching() override;

 public:
  explicit BaseSelectClause(SynonymsToSelect synonymsToSelect)
      : synonymsToSelect(std::move(synonymsToSelect)) {}

  virtual unordered_set<string> getQueryResult(
      IntermediateTable &intermediateTable) = 0;

  void addSynonymsInOtherClause(const set<string>& synonyms);

  ClauseKey getKey() override;
};
