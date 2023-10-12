#include "AssignPatternClause.h"

IntermediateTable AssignPatternClause::evaluate(Context& context,
                                          PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();
  string entityType = context.getTokenEntity(synonymValue);

  unique_ptr<AssignEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<AssignEvaluator>(
      std::move(patternArgsStream[0]), std::move(patternArgsStream[1]),
      pkbReader, isPartialMatch, synonymValue);

  return evaluatorPtr->evaluate();
}

bool AssignPatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const AssignPatternClause*>(&other);
  if (!otherPattern) return false;

  for (int i = 0; i < patternArgsStream.size(); ++i) {
    if (!(*patternArgsStream.at(i) == *otherPattern->patternArgsStream.at(i))) {
      return false;
    }
  }
  return isPartialMatch == otherPattern->isPartialMatch &&
         *synonym == *otherPattern->synonym;
}
