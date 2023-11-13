#include "IfPatternClause.h"

#include <memory>
#include <vector>

#include "qps/clause/utils/ClauseUtil.h"
#include "qps/patternEvaluator/ifEvaluator/IfEvaluator.h"

vector<const AbstractArgument*> IfPatternClause::getAllArguments() {
  vector<const AbstractArgument*> argVector;

  argVector.push_back(synonym.get());
  argVector.push_back(firstArg.get());

  return argVector;
}

IntermediateTable IfPatternClause::evaluate(PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr =
      std::make_unique<IfEvaluator>(*(this->firstArg), pkbReader, synonymValue);

  return evaluatorPtr->evaluate();
}

bool IfPatternClause::isEquals(const BaseClause& other) {
  const auto* otherPattern = dynamic_cast<const IfPatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *synonym == *otherPattern->synonym;
}

set<string> IfPatternClause::getClauseSynonyms() {
  return ClauseUtil::getSynonymArgValues(synonym, firstArg);
}

ClauseKey IfPatternClause::getKey() {
  return IF_ENTITY + ClauseUtil::KEY_DELIMITER + synonym->getArgKey() +
         ClauseUtil::KEY_DELIMITER + firstArg->getArgKey();
}
