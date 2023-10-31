#include "AssignPatternClause.h"

#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"

vector<unique_ptr<AbstractArgument>> AssignPatternClause::getAllArguments() {
  
  vector<unique_ptr<AbstractArgument>> argVector;

  argVector.push_back(std::move(synonym));
  argVector.push_back(std::move(firstArg));
  argVector.push_back(std::move(secondArg));

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
