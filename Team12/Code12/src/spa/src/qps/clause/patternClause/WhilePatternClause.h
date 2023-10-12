#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/patternEvaluator/PatternEvaluator.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"

using std::string, std::unique_ptr, std::vector;

class WhilePatternClause : public Clause {
 private:
  unique_ptr<AbstractArgument> synonym;
  unique_ptr<AbstractArgument> firstArg;

 public:
  explicit WhilePatternClause(unique_ptr<AbstractArgument> synonym,
                               unique_ptr<AbstractArgument> firstArg)
      : synonym(std::move(synonym)),
        firstArg(std::move(firstArg)) {}

  IntermediateTable evaluate(Context& context, PKBReader& pkb) override;
  bool isEquals(const Clause& other) override;
};
