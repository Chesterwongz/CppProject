#include "PatternEvaluatorFactory.h"

#include "qps/exceptions/QPSInvalidQueryException.h"

unique_ptr<PatternEvaluator> PatternEvaluatorFactory::createEvaluator(
    string& entityType, PatternArgsStream& patternArgsStream,
    PKBReader& pkbReader, bool isPartialMatch, string synonymValue) {
  if (entityType == ASSIGN_ENTITY) {
    return std::make_unique<AssignEvaluator>(
        std::move(patternArgsStream[0]), std::move(patternArgsStream[1]),
        pkbReader, isPartialMatch, synonymValue);
  }

  throw QPSInvalidQueryException("Unable to create PatternEvaluator of type: " +
                                 entityType);
}
