#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::unique_ptr;

class SuchThatClause : public Clause {
 private:
  Abstraction relationship;
  unique_ptr<AbstractArgument> firstArg;
  unique_ptr<AbstractArgument> secondArg;

 public:
  explicit SuchThatClause(Abstraction relationship,
                          unique_ptr<AbstractArgument> firstArg,
                          unique_ptr<AbstractArgument> secondArg);
  IntermediateTable evaluate(PKBReader& pkb) override;
  vector<const AbstractArgument*> getAllArguments() override;
  bool isEquals(const Clause& other) override;
  set<string> getClauseSynonyms() override;
  string getKey() override;
};
