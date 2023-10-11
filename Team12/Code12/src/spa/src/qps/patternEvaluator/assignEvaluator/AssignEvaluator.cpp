#include "AssignEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"
#include <iostream>
vector<std::pair<string, string>> AssignEvaluator::processArguments() {
  string firstArgValue = patternArgsStream[0]->getValue();
  string secondArgValue = patternArgsStream[1]->getValue();

  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();
  bool isSecondArgWildcard = patternArgsStream[1]->isWildcard();

  string secondArgRPNValue;

  if (isFirstArgSynonym) {
    firstArgValue = WILDCARD_KEYWORD;
  }
  
  if (isSecondArgWildcard) {
    secondArgRPNValue = secondArgValue;
  } else {
    secondArgRPNValue = QPSStringUtils::convertToRPN(secondArgValue);
  }

  vector<std::pair<string, string>> pkbResult;

  if (isPartialMatch) {
    pkbResult = pkbReader.getPartialAssignPattern(
        firstArgValue, secondArgRPNValue);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(
        firstArgValue, secondArgRPNValue);
  }
  
  return pkbResult;
}

IntermediateTable AssignEvaluator::buildResultTable(vector<std::pair<string, string>> pkbResult) {
  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();

  string firstArgValue = patternArgsStream[0]->getValue();

  if (isFirstArgSynonym) {
    // need to add additional variable column to result
    IntermediateTable linesSatisfyingPatternAndVarsModified =
        IntermediateTableFactory::buildIntermediateTable(
            synonymValue, firstArgValue, pkbResult);
    return linesSatisfyingPatternAndVarsModified;
  }

  // otherwise just return the single column table
  IntermediateTable linesSatisfyingPattern =
      IntermediateTableFactory::buildIntermediateTable(
          synonymValue, WILDCARD_KEYWORD, pkbResult);
  return linesSatisfyingPattern;
}
