#include "IfEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> IfEvaluator::processArguments() {
  string firstArgValue = patternArgsStream[0]->getValue();

  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();

  vector<string> pkbResult;

  // TODO(houtenteo): call pkb ifPattern API when its implemented
  // pkbResult = pkbReader.getIfPattern(firstArgValue, isFirstArgSynonym);

  return pkbResult;
}
