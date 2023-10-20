#include <string>

#include "NoSynWithEvaluator.h"

IntermediateTable NoSynWithEvaluator::evaluate() {
  string firstArgValue = firstArg->getValue();
  string secondArgValue = secondArg->getValue();

  if (firstArgValue == secondArgValue) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }

  return IntermediateTableFactory::buildEmptyIntermediateTable();
}
