#include "IfEvaluator.h"

#include <memory>

#include "qps/common/Keywords.h"

vector<pair<string, string>> IfEvaluator::evaluateArguments() {
  string firstArgValue = firstArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();

  vector<pair<string, string>> pkbResult;

  return pkbReader.getIfPattern(isFirstArgSynonym ? WILDCARD_KEYWORD
                                                  : firstArgValue);

  return pkbResult;
}
