#include "qps/clause/withClause/WithClause.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/withEvaluator/withEvaluatorFactory/WithEvaluatorFactory.h"

vector<const AbstractArgument*> WithClause::getAllArguments() {
  vector<const AbstractArgument*> argVector;

  argVector.push_back(firstArg.get());
  argVector.push_back(secondArg.get());

  return argVector;
}

IntermediateTable WithClause::evaluate(PKBReader& pkb) {
  unique_ptr<WithEvaluator> withEvaluator =
      WithEvaluatorFactory::createWithEvaluator(*(this->firstArg),
                                                *(this->secondArg), pkb);

  IntermediateTable pkbResult = withEvaluator->evaluate();

  return pkbResult;
}

bool WithClause::isEquals(const IClause& other) {
  const auto* otherClause = dynamic_cast<const WithClause*>(&other);
  if (!otherClause) return false;

  return *firstArg == *(otherClause->firstArg) &&
         *secondArg == *(otherClause->secondArg);
}
set<string> WithClause::getClauseSynonyms() {
  return ClauseUtil::getSynonymArgValues(this->firstArg, this->secondArg);
}
string WithClause::getKey() {
  return WITH_KEYWORD + "|" + firstArg->getValue() + "|" +
         secondArg->getValue();
}
