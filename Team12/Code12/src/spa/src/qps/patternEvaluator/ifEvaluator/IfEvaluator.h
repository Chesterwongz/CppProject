#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class IfEvaluator : public PatternEvaluator {
 public:
  explicit IfEvaluator(AbstractArgument& firstArg,
                       PKBReader& pkbReader, string synonymValue)
      : PatternEvaluator(firstArg, pkbReader,
                         std::move(synonymValue)) {}
  ~IfEvaluator() override = default;
  vector<pair<string, string>> evaluateArguments() override;
};
