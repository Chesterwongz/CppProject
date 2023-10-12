#include "AssignEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> AssignEvaluator::processArguments() {
  string firstArgValue = firstArg->getValue();
  string secondArgValue = secondArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgWildcard = secondArg->isWildcard();

  vector<string> pkbResult;

  if (isPartialMatch) {
    pkbResult = pkbReader.getPartialAssignPattern(firstArgValue, secondArgValue,
                                                  isFirstArgSynonym);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgValue,
                                                isFirstArgSynonym);
  }

  return pkbResult;
}
