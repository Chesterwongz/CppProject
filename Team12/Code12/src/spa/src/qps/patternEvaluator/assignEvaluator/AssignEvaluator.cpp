#include <memory>

#include "AssignEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> AssignEvaluator::processArguments() {
  string firstArgValue = firstArg->getValue();
  string secondArgValue = secondArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgWildcard = secondArg->isWildcard();

  if (isFirstArgSynonym) {
    firstArgValue = WILDCARD_KEYWORD;
  }

  vector<std::pair<string, string>> pkbResult;

  if (isPartialMatch) {
    pkbResult =
        pkbReader.getPartialAssignPattern(firstArgValue, secondArgValue);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgValue);
  }

  return pkbResult;
}
