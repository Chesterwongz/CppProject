#include <memory>

#include "AssignEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<pair<string, string>> AssignEvaluator::evaluateArguments() {
  string firstArgValue = firstArg->getValue();
  string secondArgValue = secondArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();

  if (isFirstArgSynonym) {
    firstArgValue = WILDCARD_KEYWORD;
  }

  vector<pair<string, string>> pkbResult;

  if (isPartialMatch) {
    pkbResult =
        pkbReader.getPartialAssignPattern(firstArgValue, secondArgValue);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgValue);
  }

  return pkbResult;
}
