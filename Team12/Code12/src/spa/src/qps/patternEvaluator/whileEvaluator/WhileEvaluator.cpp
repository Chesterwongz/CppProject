#include "WhileEvaluator.h"

#include <memory>

#include "qps/common/Keywords.h"

vector<pair<string, string>> WhileEvaluator::evaluateArguments() {
  string firstArgValue = firstArg.getValue();

  bool isFirstArgSynonym = firstArg.isSynonym();

  vector<pair<string, string>> pkbResult;

  return pkbReader.getWhilePattern(isFirstArgSynonym ? WILDCARD_KEYWORD
                                                     : firstArgValue);

  return pkbResult;
}
