#include "WhilePatternClause.h"

#include <memory>
#include <vector>

#include "qps/clause/utils/ClauseUtil.h"
#include "qps/patternEvaluator/whileEvaluator/WhileEvaluator.h"

vector<const AbstractArgument*> WhilePatternClause::getAllArguments() {
  vector<const AbstractArgument*> argVector;

  argVector.push_back(synonym.get());
  argVector.push_back(firstArg.get());

  return argVector;
}

IntermediateTable WhilePatternClause::evaluate(PKBReader& pkbReader) {
  string synonymValue = synonym->getValue();

  unique_ptr<PatternEvaluator> evaluatorPtr;

  evaluatorPtr = std::make_unique<WhileEvaluator>(*(this->firstArg), pkbReader,
                                                  synonymValue);

  return evaluatorPtr->evaluate();
}

bool WhilePatternClause::isEquals(const BaseClause& other) {
  const auto* otherPattern = dynamic_cast<const WhilePatternClause*>(&other);
  if (!otherPattern) return false;

  return *firstArg == *(otherPattern->firstArg) &&
         *synonym == *otherPattern->synonym;
}

set<string> WhilePatternClause::getClauseSynonyms() {
  return ClauseUtil::getSynonymArgValues(synonym, firstArg);
}

ClauseKey WhilePatternClause::getKey() {
  return WHILE_ENTITY + ClauseUtil::KEY_DELIMITER + synonym->getArgKey() +
         ClauseUtil::KEY_DELIMITER + firstArg->getArgKey();
}
