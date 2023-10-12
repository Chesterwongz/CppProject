#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class AssignEvaluator : public PatternEvaluator {
 public:
  explicit AssignEvaluator(PatternArgsStream& patternArgsStream,
                           PKBReader& pkbReader, bool isPartialMatch,
                           string synonymValue)
      : PatternEvaluator(patternArgsStream, pkbReader, isPartialMatch,
                         synonymValue) {}
  ~AssignEvaluator() override = default;
  vector<string> processArguments() override;
};
