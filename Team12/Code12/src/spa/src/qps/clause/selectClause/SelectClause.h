#pragma once

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

typedef vector<unique_ptr<SynonymArg>> SynonymsToSelect;

class SelectClause : public Clause {
 private:
  SynonymsToSelect synonymsToSelect;
  static IntermediateTable getAllPossibleValues(PKBReader &pkb,
      unique_ptr<SynonymArg> &synonymArg);

 public:
  explicit SelectClause(SynonymsToSelect synonymsToSelect);
  IntermediateTable evaluate(PKBReader &pkb) override;
  bool isEquals(const Clause &other) override;
};

typedef std::function<set<string>(PKBReader &pkb)> evaluatorFunc;
static inline unordered_map<Entity, evaluatorFunc> evaluatorFuncMap = {
    {PROCEDURE_ENTITY, [](PKBReader &pkb) { return pkb.getAllProcedures(); }},
    {VARIABLE_ENTITY, [](PKBReader &pkb) { return pkb.getAllVariables(); }},
    {CONSTANT_ENTITY, [](PKBReader &pkb) { return pkb.getAllConstants(); }},
};
