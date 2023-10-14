#include "IfEvaluator.h"

#include <memory>

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<pair<string, string>> IfEvaluator::evaluateArguments() {
  string firstArgValue = firstArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();

  vector<pair<string, string>> pkbResult;

  if (isFirstArgSynonym) {
    pkbResult = pkbReader.getIfPattern(WILDCARD_KEYWORD);
  } else {
    pkbResult = pkbReader.getIfPattern(firstArgValue);
  }

  return pkbResult;
}
