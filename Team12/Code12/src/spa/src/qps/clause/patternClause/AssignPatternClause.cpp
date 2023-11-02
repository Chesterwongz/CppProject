#include "AssignPatternClause.h"

#include "qps/clause/utils/ClauseUtil.h"
#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"

IntermediateTable AssignPatternClause::evaluate(PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<AssignEvaluator>(
      firstArg, secondArg, pkbReader, isPartialMatch, synonymValue);

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

set<string> AssignPatternClause::getClauseSynonyms() {
  return ClauseUtil::getSynonymArgValues(firstArg, secondArg);
}

string AssignPatternClause::getKey() {
  return ASSIGN_ENTITY + '|' + synonym->getValue() + '|' +
         firstArg->getValue() + '|' + secondArg->getValue();
}
