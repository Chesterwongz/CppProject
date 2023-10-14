#include "PatternEvaluator.h"

IntermediateTable PatternEvaluator::evaluate() {
  vector<std::pair<string, string>> pkbResult = processArguments();

  IntermediateTable result = buildResultTable(pkbResult);
  return result;
}

IntermediateTable PatternEvaluator::buildResultTable(vector<string> pkbResult) {
  bool isFirstArgSynonym = firstArg->isSynonym();

  string firstArgValue = firstArg->getValue();

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
