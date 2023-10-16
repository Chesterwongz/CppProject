#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class WhileEvaluator : public PatternEvaluator {
 public:
  explicit WhileEvaluator(unique_ptr<AbstractArgument> firstArg,
                          PKBReader& pkbReader, string synonymValue)
      : PatternEvaluator(std::move(firstArg), pkbReader,
                         std::move(synonymValue)) {}
  ~WhileEvaluator() override = default;
  vector<pair<string, string>> evaluateArguments() override;
};
