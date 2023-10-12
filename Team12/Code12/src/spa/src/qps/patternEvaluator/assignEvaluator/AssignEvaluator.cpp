#include "AssignEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"
#include <iostream>
vector<std::pair<string, string>> AssignEvaluator::processArguments() {
  string firstArgValue = patternArgsStream[0]->getValue();
  string secondArgValue = patternArgsStream[1]->getValue();

  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();

  if (isFirstArgSynonym) {
    firstArgValue = WILDCARD_KEYWORD;
  }

  vector<std::pair<string, string>> pkbResult;

  if (isPartialMatch) {
    pkbResult = pkbReader.getPartialAssignPattern(
        firstArgValue, secondArgValue);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(
        firstArgValue, secondArgValue);
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
