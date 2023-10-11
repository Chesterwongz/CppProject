#include "AssignEvaluator.h"

#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

vector<std::pair<string, string>> AssignEvaluator::processArguments() {
  string firstArgValue = patternArgsStream[0]->getValue();
  string secondArgValue = patternArgsStream[1]->getValue();

  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();
  bool isSecondArgWildcard = patternArgsStream[1]->isWildcard();

  string secondArgRPNValue;

  if (isSecondArgWildcard) {
    secondArgRPNValue = secondArgValue;
  } else {
    secondArgRPNValue = QPSStringUtils::convertToRPN(secondArgValue);
  }

  vector<std::pair<string, string>> pkbResult;

  if (isPartialMatch) {
    pkbResult = pkbReader.getPartialAssignPattern(
        firstArgValue, secondArgRPNValue, isFirstArgSynonym);
  } else {
    pkbResult = pkbReader.getExactAssignPattern(
        firstArgValue, secondArgRPNValue, isFirstArgSynonym);
  }

  return pkbResult;
}

IntermediateTable AssignEvaluator::buildResultTable(vector<std::pair<string, string>> pkbResult) {
  bool isFirstArgSynonym = patternArgsStream[0]->isSynonym();

  string firstArgValue = patternArgsStream[0]->getValue();

  IntermediateTable linesSatisfyingPattern =
      IntermediateTableFactory::buildSingleColTable(synonymValue, pkbResult);

  if (isFirstArgSynonym) {
    // need to add additional variable column to result
    const string& varColName = firstArgValue;

    vector<pair<string, string>> lineVariablePairs =
        pkbReader.getAllModifiedVariables(StmtType::ASSIGN);

    IntermediateTable lineAndVarsModified =
        IntermediateTableFactory::buildIntermediateTable(
            synonymValue, varColName, lineVariablePairs);

    IntermediateTable linesSatisfyingPatternAndVarsModified =
        linesSatisfyingPattern.join(lineAndVarsModified);

    return linesSatisfyingPatternAndVarsModified;
  }

  // otherwise just return the single column table
  return linesSatisfyingPattern;
}
