#include "WhilePatternClause.h"

#include <memory>

#include "qps/patternEvaluator/whileEvaluator/WhileEvaluator.h"

IntermediateTable WhilePatternClause::evaluate(PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<WhileEvaluator>(*(this->firstArg),
                                                  pkbReader, synonymValue);

  return evaluatorPtr->evaluate();
}

bool WhilePatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const WhilePatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *synonym == *otherPattern->synonym;
}
