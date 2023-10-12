#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class WhileEvaluator : public PatternEvaluator {
 public:
  explicit WhileEvaluator(PatternArgsStream& patternArgsStream,
                          PKBReader& pkbReader, bool isPartialMatch,
                          string synonymValue)
      : PatternEvaluator(patternArgsStream, pkbReader, isPartialMatch,
                         synonymValue) {}
  ~WhileEvaluator() override = default;
  vector<string> processArguments() override;
};
