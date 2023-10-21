#include "PatternEvaluator.h"

#include "qps/abstraction/SynResConversionUtils.h"
#include "qps/clause/utils/ClauseUtil.h"

IntermediateTable PatternEvaluator::evaluate() {
  vector<std::pair<string, string>> pkbResult = evaluateArguments();

  IntermediateTable result = buildResultTable(pkbResult);
  return result;
}

IntermediateTable PatternEvaluator::buildResultTable(
    const vector<pair<string, string>>& pkbResult) {
  bool isFirstArgSynonym = firstArg->isSynonym();
  string firstArgValue = firstArg->getValue();

  Entity firstArgEntity = ClauseUtil::getArgEntity(*firstArg);
  vector<vector<SynonymRes>> resultAsSynonymRes =
      SynResConversionUtils::toSynonymRes(
          pkbResult, {firstArgEntity, VARIABLE_ENTITY}, pkbReader);

  if (isFirstArgSynonym) {
    // need to add additional variable column to result
    const string& varColName = firstArgValue;

    IntermediateTable linesSatisfyingPatternAndVarsModified =
        IntermediateTableFactory::buildIntermediateTable(
            {synonymValue, varColName}, resultAsSynonymRes);

    return linesSatisfyingPatternAndVarsModified;
  }

  // otherwise just return the single column table
  IntermediateTable linesSatisfyingPattern =
      IntermediateTableFactory::buildIntermediateTable(
          {synonymValue, WILDCARD_KEYWORD}, resultAsSynonymRes);

  return linesSatisfyingPattern;
}
