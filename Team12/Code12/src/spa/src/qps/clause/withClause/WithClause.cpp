#include "qps/clause/withClause/WithClause.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/withEvaluator/WithEvaluatorFactory/WithEvaluatorFactory.h"

IntermediateTable WithClause::evaluate(PKBReader& pkb) {
  unique_ptr<WithEvaluator> withEvaluator =
      WithEvaluatorFactory::createWithEvaluator(std::move(firstArg),
                                                std::move(secondArg), pkb);

  IntermediateTable pkbResult = withEvaluator->evaluate();

  return pkbResult;
}

bool WithClause::isEquals(const Clause& other) {
  const auto* otherClause = dynamic_cast<const WithClause*>(&other);
  if (!otherClause) return false;

  return *firstArg == *(otherClause->firstArg) &&
         *secondArg == *(otherClause->secondArg);
}
set<string> WithClause::getClauseSynonyms() {
  return {firstArg->getValue(), secondArg->getValue()};
}
