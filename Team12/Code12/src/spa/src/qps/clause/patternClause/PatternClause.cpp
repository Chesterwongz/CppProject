#include "PatternClause.h"

IntermediateTable PatternClause::evaluate(Context& context,
                                          PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();
  string entityType = context.getTokenEntity(synonymValue);

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = PatternEvaluatorFactory::createEvaluator(
      entityType, context, patternArgsStream, pkbReader, isPartialMatch,
      synonymValue);

  return evaluatorPtr->evaluate();
}

bool PatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const PatternClause*>(&other);
  if (!otherPattern) return false;

  for (int i = 0; i < patternArgsStream.size(); ++i) {
    if (!(*patternArgsStream.at(i) == *otherPattern->patternArgsStream.at(i))) {
      return false;
    }
  }
  return isPartialMatch == otherPattern->isPartialMatch &&
         *synonym == *otherPattern->synonym;
}
