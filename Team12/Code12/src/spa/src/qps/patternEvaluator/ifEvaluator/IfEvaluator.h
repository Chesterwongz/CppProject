#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class IfEvaluator : public PatternEvaluator {
 public:
  explicit IfEvaluator(unique_ptr<AbstractArgument> firstArg,
                       PKBReader& pkbReader, string synonymValue)
      : PatternEvaluator(std::move(firstArg), pkbReader, synonymValue) {}
  ~IfEvaluator() override = default;
  vector<string> processArguments() override;
};
