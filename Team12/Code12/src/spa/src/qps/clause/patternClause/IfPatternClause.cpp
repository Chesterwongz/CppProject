#include <memory>

#include "IfPatternClause.h"
#include "qps/patternEvaluator/ifEvaluator/IfEvaluator.h"

IntermediateTable IfPatternClause::evaluate(Context& context,
                                               PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<IfEvaluator>(std::move(firstArg),
                                                  pkbReader, synonymValue);

  return evaluatorPtr->evaluate();
}

bool IfPatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const IfPatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *synonym == *otherPattern->synonym;
}
