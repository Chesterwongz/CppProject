#include "AssignPatternClause.h"

#include <vector>

#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"

vector<const AbstractArgument*> AssignPatternClause::getAllArguments() {
  vector<const AbstractArgument*> argVector;

  argVector.push_back(synonym.get());
  argVector.push_back(firstArg.get());
  argVector.push_back(secondArg.get());

  return argVector;
}

IntermediateTable AssignPatternClause::evaluate(PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<AssignEvaluator>(
      *(this->firstArg), *(this->secondArg), pkbReader, isPartialMatch,
      synonymValue);

  return evaluatorPtr->evaluate();
}

bool AssignPatternClause::isEquals(const Clause& other) {
  const auto* otherPattern = dynamic_cast<const AssignPatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *secondArg == *(otherPattern->secondArg) &&
         isPartialMatch == otherPattern->isPartialMatch &&
         *synonym == *otherPattern->synonym;
}
