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
#include "qps/clause/IClause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

class BaseSelectClause : public IClause {
 protected:
  SynonymsToSelect synonymsToSelect;
  set<string> synonymsInOtherClauses;

 public:
  explicit BaseSelectClause(SynonymsToSelect synonymsToSelect)
      : synonymsToSelect(std::move(synonymsToSelect)) {}

  virtual unordered_set<string> getQueryResult(
      IntermediateTable &intermediateTable) = 0;

  void addSynonymsInOtherClause(const set<string>& synonyms);

  string getKey() override;
};
