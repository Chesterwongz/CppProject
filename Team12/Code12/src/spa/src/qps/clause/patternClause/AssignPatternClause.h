#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/patternEvaluator/PatternEvaluator.h"

using std::string, std::unique_ptr, std::vector;

class AssignPatternClause : public Clause {
 private:
  unique_ptr<AbstractArgument> synonym;
  unique_ptr<AbstractArgument> firstArg;
  unique_ptr<AbstractArgument> secondArg;
  bool isPartialMatch;

 public:
  explicit AssignPatternClause(unique_ptr<AbstractArgument> synonym,
                               unique_ptr<AbstractArgument> firstArg,
                               unique_ptr<AbstractArgument> secondArg,
                               bool isPartialMatch)
      : synonym(std::move(synonym)),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)),
        isPartialMatch(isPartialMatch) {}

  IntermediateTable evaluate(PKBReader& pkb) override;
  bool isEquals(const Clause& other) override;
  set<string> getClauseSynonyms() override;
};
