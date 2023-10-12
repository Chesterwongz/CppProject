#include <memory>

#include "IfEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> IfEvaluator::processArguments() {
  string firstArgValue = firstArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();

  vector<string> pkbResult;

  // TODO(houtenteo): call pkb ifPattern API when its implemented
  // pkbResult = pkbReader.getIfPattern(firstArgValue, isFirstArgSynonym);

  return pkbResult;
}
