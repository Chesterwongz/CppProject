#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

class SelectBooleanClause : public BaseSelectClause {
 public:
  explicit SelectBooleanClause(SynonymsToSelect synonymsToSelect)
      : BaseSelectClause(std::move(synonymsToSelect)) {}

  IntermediateTable evaluate(PKBReader &pkb) override;

  bool isEquals(const Clause &other) override;

  unordered_set<string> getQueryResult(
      IntermediateTable &intermediateTable) override;

  set<string> getClauseSynonyms() override;
};

namespace SelectBooleanClauseUtils {
const unordered_set<string> TRUE_RESULT = {"TRUE"};
const unordered_set<string> FALSE_RESULT = {"FALSE"};
}  // namespace SelectBooleanClauseUtils
