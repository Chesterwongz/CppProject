#include "PatternEvaluator.h"

IntermediateTable PatternEvaluator::evaluate() {
  vector<string> pkbResult = processArguments();

  IntermediateTable result = buildResultTable(pkbResult);

  return result;
}
