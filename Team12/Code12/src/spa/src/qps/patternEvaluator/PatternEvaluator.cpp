#include "PatternEvaluator.h"

IntermediateTable PatternEvaluator::evaluate() {
  vector<std::pair<string, string>> pkbResult = processArguments();

  IntermediateTable result = buildResultTable(pkbResult);

  return result;
}
