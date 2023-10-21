#include "qps/withEvaluator/doubleSynWithEvaluator/DoubleSynWithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable DoubleSynWithEvaluator::evaluate() {
  string firstSynonymValue = firstSynonymArg->getValue();
  Entity firstEntityType = firstSynonymArg->getEntityType();
  AttrRef firstAttrRef = firstSynonymArg->getAttrRef();
  pair<string, AttrRef> firstColNameAttrRefPair = {firstSynonymValue,
                                                   firstAttrRef};

  string secondSynonymValue = secondSynonymArg->getValue();
  Entity secondEntityType = secondSynonymArg->getEntityType();
  AttrRef secondAttrRef = secondSynonymArg->getAttrRef();
  pair<string, AttrRef> secondColNameAttrRefPair = {secondSynonymValue,
                                                    secondAttrRef};

  vector<SynonymRes> firstPKBResult = withEvaluatorFuncMap[firstEntityType]();
  IntermediateTable firstResult = IntermediateTableFactory::buildSingleColTable(
      firstSynonymValue, firstPKBResult);

  vector<SynonymRes> secondPKBResult = withEvaluatorFuncMap[secondEntityType]();
  IntermediateTable secondResult =
      IntermediateTableFactory::buildSingleColTable(secondSynonymValue,
                                                    secondPKBResult);

  return firstResult.join(secondResult, firstColNameAttrRefPair,
                             secondColNameAttrRefPair);
}
