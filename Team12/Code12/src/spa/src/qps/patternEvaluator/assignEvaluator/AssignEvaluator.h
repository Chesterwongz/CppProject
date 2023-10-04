#pragma once

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
  vector<string> processArguments() override;
  IntermediateTable buildResultTable(vector<string> pkbResult) override;
};
