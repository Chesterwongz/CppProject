#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "qps/patternEvaluator/PatternEvaluator.h"

class WhileEvaluator : public PatternEvaluator {
 public:
  explicit WhileEvaluator(unique_ptr<AbstractArgument> firstArg,
                          PKBReader& pkbReader, string synonymValue)
      : PatternEvaluator(std::move(firstArg), pkbReader, synonymValue) {}
  ~WhileEvaluator() override = default;
  vector<pair<string, string>> evaluateArguments() override;
};
