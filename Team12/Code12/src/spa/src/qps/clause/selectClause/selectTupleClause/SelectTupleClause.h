#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/selectClause/ISelectClause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

class SelectTupleClause : public ISelectClause {
 private:
  static IntermediateTable getAllPossibleValues(
      PKBReader &pkb, unique_ptr<SynonymArg> &synonymArg);

 public:
  explicit SelectTupleClause(SynonymsToSelect synonymsToSelect)
      : ISelectClause(std::move(synonymsToSelect)) {};

  IntermediateTable evaluate(PKBReader &pkb) override;

  bool isEquals(const Clause &other) override;

  unordered_set<string> getQueryResult(
      IntermediateTable &intermediateTable) override;
};

typedef std::function<vector<string>(PKBReader &pkb)> evaluatorFunc;
namespace SelectTupleClauseUtils {
static inline unordered_map<Entity, evaluatorFunc> evaluatorFuncMap = {
    {PROCEDURE_ENTITY, [](PKBReader &pkb) { return pkb.getAllProcedures(); }},
    {VARIABLE_ENTITY, [](PKBReader &pkb) { return pkb.getAllVariables(); }},
    {CONSTANT_ENTITY, [](PKBReader &pkb) { return pkb.getAllConstants(); }},
};
}
