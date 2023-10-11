#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/patternEvaluator/PatternEvaluator.h"

class AssignEvaluator : public PatternEvaluator {
 public:
  explicit AssignEvaluator(Context& context,
                           PatternArgsStream& patternArgsStream,
                           PKBReader& pkbReader, bool isPartialMatch,
                           string synonymValue)
      : PatternEvaluator(context, patternArgsStream, pkbReader, isPartialMatch,
                         synonymValue) {}
  ~AssignEvaluator() override = default;
  vector<std::pair<string, string>> processArguments() override;
  IntermediateTable buildResultTable(vector<std::pair<string, string>> pkbResult) override;
};
