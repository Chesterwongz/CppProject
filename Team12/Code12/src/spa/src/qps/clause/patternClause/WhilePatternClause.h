#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/patternEvaluator/PatternEvaluator.h"

using std::string, std::unique_ptr, std::vector;

class WhilePatternClause : public Clause {
 private:
  unique_ptr<AbstractArgument> synonym;
  unique_ptr<AbstractArgument> firstArg;

 public:
  explicit WhilePatternClause(unique_ptr<AbstractArgument> synonym,
                              unique_ptr<AbstractArgument> firstArg)
      : synonym(std::move(synonym)), firstArg(std::move(firstArg)) {}

  IntermediateTable evaluate(PKBReader& pkb) override;
  vector<const AbstractArgument*> getAllArguments() override;
  bool isEquals(const BaseClause& other) override;
  set<string> getClauseSynonyms() override;
  ClauseKey getKey() override;
};
