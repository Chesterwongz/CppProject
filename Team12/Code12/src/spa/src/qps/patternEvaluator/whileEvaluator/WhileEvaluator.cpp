#include <memory>

#include "WhileEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> WhileEvaluator::processArguments() {
  string firstArgValue = firstArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();

  vector<string> pkbResult;

  // TODO(houtenteo): call pkb whilePattern API when its implemented
  // pkbResult = pkbReader.getWhilePattern(firstArgValue, isFirstArgSynonym);

  return pkbResult;
}
