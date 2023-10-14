#include "PatternEvaluator.h"

IntermediateTable PatternEvaluator::evaluate() {
  vector<std::pair<string, string>> pkbResult = evaluateArguments();

  IntermediateTable result = buildResultTable(pkbResult);
  return result;
}

IntermediateTable PatternEvaluator::buildResultTable(
    vector<pair<string, string>> pkbResult) {
  bool isFirstArgSynonym = firstArg->isSynonym();

  string firstArgValue = firstArg->getValue();

  if (isFirstArgSynonym) {
    // need to add additional variable column to result
    const string& varColName = firstArgValue;

    IntermediateTable linesSatisfyingPatternAndVarsModified =
        IntermediateTableFactory::buildIntermediateTable(
            synonymValue, varColName, pkbResult);

    return linesSatisfyingPatternAndVarsModified;
  }

  // otherwise just return the single column table
  IntermediateTable linesSatisfyingPattern =
      IntermediateTableFactory::buildIntermediateTable(
          synonymValue, WILDCARD_KEYWORD, pkbResult);

  return linesSatisfyingPattern;
}
