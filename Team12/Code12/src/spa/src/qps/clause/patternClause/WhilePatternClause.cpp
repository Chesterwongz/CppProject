#include "WhilePatternClause.h"

#include <memory>

#include "qps/patternEvaluator/whileEvaluator/WhileEvaluator.h"

IntermediateTable WhilePatternClause::evaluate(Context& context,
                                               PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();
  string entityType = context.getTokenEntity(synonymValue);

  unique_ptr<WhileEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<WhileEvaluator>(std::move(firstArg),
                                                  pkbReader, synonymValue);

  return evaluatorPtr->evaluate();
}

bool WhilePatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const WhilePatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *synonym == *otherPattern->synonym;
}
