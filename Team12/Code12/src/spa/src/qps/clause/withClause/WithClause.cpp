#include "qps/clause/withClause/WithClause.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/withEvaluator/WithEvaluatorFactory/WithEvaluatorFactory.h"

vector<unique_ptr<AbstractArgument>> WithClause::getAllArguments() {
  vector<unique_ptr<AbstractArgument>> argVector;

  argVector.push_back(std::move(firstArg));
  argVector.push_back(std::move(secondArg));

  return argVector;
}

IntermediateTable WithClause::evaluate(PKBReader& pkb) {
  unique_ptr<WithEvaluator> withEvaluator =
      WithEvaluatorFactory::createWithEvaluator(*(this->firstArg),
                                                *(this->secondArg), pkb);

  IntermediateTable pkbResult = withEvaluator->evaluate();

  return pkbResult;
}

bool WithClause::isEquals(const Clause& other) {
  const auto* otherClause = dynamic_cast<const WithClause*>(&other);
  if (!otherClause) return false;

  return *firstArg == *(otherClause->firstArg) &&
         *secondArg == *(otherClause->secondArg);
}
