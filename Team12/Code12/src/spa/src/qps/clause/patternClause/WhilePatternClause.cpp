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

set<string> WhilePatternClause::getClauseSynonyms() {
  return ClauseUtil::getSynonymArgValues(synonym, firstArg);
}

string WhilePatternClause::getKey() {
  return WHILE_ENTITY + '|' + synonym->getValue() + '|' + firstArg->getValue();
}
