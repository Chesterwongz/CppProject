#pragma once

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

typedef std::function<vector<string>(PKBReader &pkb)> evaluatorFunc;

class SelectTupleClause : public BaseSelectClause {
 private:
  static inline const unordered_map<Entity, evaluatorFunc> evaluatorFuncMap = {
      {PROCEDURE_ENTITY, [](PKBReader &pkb) { return pkb.getAllProcedures(); }},
      {VARIABLE_ENTITY, [](PKBReader &pkb) { return pkb.getAllVariables(); }},
      {CONSTANT_ENTITY, [](PKBReader &pkb) { return pkb.getAllConstants(); }},
  };

  static IntermediateTable getAllPossibleValues(
      PKBReader &pkb, unique_ptr<SynonymArg> &synonymArg);

 public:
  explicit SelectTupleClause(SynonymsToSelect synonymsToSelect)
      : BaseSelectClause(std::move(synonymsToSelect)) {}

  IntermediateTable evaluate(PKBReader &pkb) override;

  bool isEquals(const IClause& other) override;

  unordered_set<string> getQueryResult(
      IntermediateTable &intermediateTable) override;

  set<string> getClauseSynonyms() override;
};
