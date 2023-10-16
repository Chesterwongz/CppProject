#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "qps/patternEvaluator/PatternEvaluator.h"

class IfEvaluator : public PatternEvaluator {
 public:
  explicit IfEvaluator(unique_ptr<AbstractArgument> firstArg,
                       PKBReader& pkbReader, string synonymValue)
      : PatternEvaluator(std::move(firstArg), pkbReader, std::move(synonymValue)) {}
  ~IfEvaluator() override = default;
  vector<pair<string, string>> evaluateArguments() override;
};
