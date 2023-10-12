#include "AssignEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> AssignEvaluator::processArguments() {
  string firstArgValue = firstArg->getValue();
  string secondArgValue = secondArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgWildcard = secondArg->isWildcard();

  string secondArgRPNValue;

  if (isSecondArgWildcard) {
    secondArgRPNValue = secondArgValue;
  } else {
    secondArgRPNValue = QPSStringUtils::convertToRPN(secondArgValue);
  }

  vector<string> pkbResult;

  if (isPartialMatch) {
    pkbResult = pkbReader.getPartialAssignPattern(
        firstArgValue, secondArgRPNValue, isFirstArgSynonym);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(
        firstArgValue, secondArgRPNValue, isFirstArgSynonym);
  }

  return pkbResult;
}
