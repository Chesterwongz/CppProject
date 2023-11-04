#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class AssignEvaluator : public PatternEvaluator {
 protected:
  AbstractArgument& secondArg;
  bool isPartialMatch;

 public:
  explicit AssignEvaluator(AbstractArgument& firstArg,
                           AbstractArgument& secondArg,
                           PKBReader& pkbReader, bool isPartialMatch,
                           string synonymValue)
      : PatternEvaluator(firstArg, pkbReader,
                         std::move(synonymValue)),
        secondArg(secondArg),
        isPartialMatch(isPartialMatch) {}
  ~AssignEvaluator() override = default;
  vector<pair<string, string>> evaluateArguments() override;
};
