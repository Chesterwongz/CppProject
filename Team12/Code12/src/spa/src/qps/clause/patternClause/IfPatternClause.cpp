#include "IfPatternClause.h"

#include <memory>

#include "qps/patternEvaluator/ifEvaluator/IfEvaluator.h"

vector<unique_ptr<AbstractArgument>> IfPatternClause::getAllArguments() {
  vector<unique_ptr<AbstractArgument>> argVector;

  argVector.push_back(std::move(synonym));
  argVector.push_back(std::move(firstArg));

  return argVector;
}

IntermediateTable IfPatternClause::evaluate(PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<IfEvaluator>(*(this->firstArg), pkbReader,
                                               synonymValue);

  return evaluatorPtr->evaluate();
}

bool IfPatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const IfPatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *synonym == *otherPattern->synonym;
}
