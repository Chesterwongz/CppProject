#include "AssignEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> AssignEvaluator::processArguments() {
  string firstArgValue = patternArgsStream[0]->getValue();
  string secondArgValue = patternArgsStream[1]->getValue();

  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();
  bool isSecondArgWildcard = patternArgsStream[1]->isWildcard();

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
