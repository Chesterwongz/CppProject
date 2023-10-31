#include "WhilePatternClause.h"

#include <memory>
#include <vector>

#include "qps/patternEvaluator/whileEvaluator/WhileEvaluator.h"

vector<unique_ptr<AbstractArgument>> WhilePatternClause::getAllArguments() {
  vector<unique_ptr<AbstractArgument>> argVector;

  argVector.push_back(std::move(synonym));
  argVector.push_back(std::move(firstArg));

  return argVector;
}

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
