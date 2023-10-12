#pragma once

#include <memory>
#include <string>

#include "assignEvaluator/AssignEvaluator.h"
#include "qps/common/Keywords.h"
#include "qps/context/Context.h"

using std::string, std::unique_ptr;

class PatternEvaluatorFactory {
 public:
  static unique_ptr<PatternEvaluator> createEvaluator(
      string& entityType, PatternArgsStream& patternArgsStream,
      PKBReader& pkbReader, bool isPartialMatch, string synonymValue);
};
