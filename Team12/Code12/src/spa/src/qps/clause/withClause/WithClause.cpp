#include "qps/clause/withClause/WithClause.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/withEvaluator/WithEvaluatorFactory.h"

IntermediateTable WithClause::evaluate(PKBReader& pkb) {

  unique_ptr<WithEvaluator> withEvaluator = WithEvaluatorFactory::createWithEvaluator(
      move(firstArg), move(secondArg));

  IntermediateTable pkbResult = withEvaluator->evaluate(pkb);
  
  return pkbResult;
}

bool WithClause::isEquals(const Clause& other) {
  const auto* otherClause = dynamic_cast<const WithClause*>(&other);
  if (!otherClause) return false;

  return *firstArg == *(otherClause->firstArg) &&
         *secondArg == *(otherClause->secondArg);
}
