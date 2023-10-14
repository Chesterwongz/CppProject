#include "WhileEvaluator.h"

#include <memory>

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<pair<string, string>> WhileEvaluator::processArguments() {
  string firstArgValue = firstArg->getValue();

  bool isFirstArgSynonym = firstArg->isSynonym();

  vector<pair<string, string>> pkbResult;

  if (isFirstArgSynonym) {
    pkbResult = pkbReader.getWhilePattern(WILDCARD_KEYWORD);
  } else {
    pkbResult = pkbReader.getWhilePattern(firstArgValue);
  }

  return pkbResult;
}
