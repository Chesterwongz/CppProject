#include "NoSynWithEvaluator.h"

IntermediateTable NoSynWithEvaluator::evaluate(PKBReader& pkbReader) {
  string firstArgValue = firstArg->getValue();
  string secondArgValue = secondArg->getValue();

  if (firstArgValue == secondArgValue) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }

  return IntermediateTableFactory::buildEmptyIntermediateTable();
}
