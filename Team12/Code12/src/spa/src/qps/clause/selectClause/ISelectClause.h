#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

class ISelectClause : public Clause {
 protected:
  SynonymsToSelect synonymsToSelect;

 public:
  explicit ISelectClause(SynonymsToSelect synonymsToSelect)
      : synonymsToSelect(std::move(synonymsToSelect)) {}
  virtual unordered_set<string> getQueryResult(
      IntermediateTable &intermediateTable) = 0;
  vector<AbstractArgument*> getAllArguments() override;
};
