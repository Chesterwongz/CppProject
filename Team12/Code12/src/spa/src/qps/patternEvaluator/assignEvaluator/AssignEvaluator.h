#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class AssignEvaluator : public PatternEvaluator {
 protected:
  unique_ptr<AbstractArgument> secondArg;

 public:
  explicit AssignEvaluator(unique_ptr<AbstractArgument> firstArg,
                           unique_ptr<AbstractArgument> secondArg,
                           PKBReader& pkbReader, bool isPartialMatch,
                           string synonymValue)
      : PatternEvaluator(std::move(firstArg), pkbReader, isPartialMatch,
                         synonymValue),
        secondArg(std::move(secondArg)) {}
  ~AssignEvaluator() override = default;
  vector<string> processArguments() override;
};
