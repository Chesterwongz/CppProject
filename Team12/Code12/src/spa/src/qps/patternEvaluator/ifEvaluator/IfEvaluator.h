#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class IfEvaluator : public PatternEvaluator {
 public:
  explicit IfEvaluator(PatternArgsStream& patternArgsStream,
                       PKBReader& pkbReader, bool isPartialMatch,
                       string synonymValue)
      : PatternEvaluator(patternArgsStream, pkbReader, isPartialMatch,
                         synonymValue) {}
  ~IfEvaluator() override = default;
  vector<string> processArguments() override;
};
