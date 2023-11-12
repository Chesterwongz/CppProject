#include "AssignPatternClause.h"

#include <vector>

#include "qps/clause/utils/ClauseUtil.h"
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

bool AssignPatternClause::isEquals(const BaseClause& other) {
  const auto* otherPattern = dynamic_cast<const AssignPatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *secondArg == *(otherPattern->secondArg) &&
         isPartialMatch == otherPattern->isPartialMatch &&
         *synonym == *otherPattern->synonym;
}

set<string> AssignPatternClause::getClauseSynonyms() {
  set<string> clauseSynonyms =
      ClauseUtil::getSynonymArgValues(firstArg, secondArg);
  clauseSynonyms.insert(synonym->getValue());
  return clauseSynonyms;
}

ClauseKey AssignPatternClause::getKey() {
  return ASSIGN_ENTITY + ClauseUtil::KEY_DELIMITER + synonym->getValue() +
         ClauseUtil::KEY_DELIMITER + firstArg->getValue() +
         ClauseUtil::KEY_DELIMITER + secondArg->getValue();
}
