#include "WhileEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<string> WhileEvaluator::processArguments() {
  string firstArgValue = patternArgsStream[0]->getValue();

  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();

  vector<string> pkbResult;

  // TODO: call pkb whilePattern API when its implemented
  // pkbResult = pkbReader.getWhilePattern(firstArgValue, isFirstArgSynonym);

  return pkbResult;
}
