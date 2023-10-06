#pragma once

#include <functional>

#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/argument/AbstractArgument.h"

using std::unique_ptr;

typedef vector<unique_ptr<AbstractArgument>> SynonymsToSelect;

class SelectClause : public Clause {
 private:
  SynonymsToSelect synonymsToSelect;
  IntermediateTable getAllPossibleValues(
      Context &context, PKBReader &pkb,
      unique_ptr<AbstractArgument> &synonymArg);

 public:
  explicit SelectClause(SynonymsToSelect synonymsToSelect);
  IntermediateTable evaluate(Context &context, PKBReader &pkb) override;
  bool isEquals(const Clause &other) override;
};

typedef std::function<set<string>(PKBReader &pkb)> evaluatorFunc;
inline unordered_map<Entity, evaluatorFunc> evaluatorFuncMap = {
    {PROCEDURE_ENTITY, [](PKBReader &pkb) { return pkb.getAllProcedures(); }},
    {VARIABLE_ENTITY, [](PKBReader &pkb) { return pkb.getAllVariables(); }},
    {CONSTANT_ENTITY, [](PKBReader &pkb) { return pkb.getAllConstants(); }},
};
