#include "qps/withEvaluator/doubleSynWithEvaluator/DoubleSynWithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable DoubleSynWithEvaluator::evaluate() {
  string firstSynonymValue = firstSynonymArg->getValue();
  Entity firstEntityType = firstSynonymArg->getEntityType();
  AttrRef firstAttrRef = firstSynonymArg->getAttrRef();

  string secondSynonymValue = secondSynonymArg->getValue();
  Entity secondEntityType = secondSynonymArg->getEntityType();
  AttrRef secondAttrRef = secondSynonymArg->getAttrRef();

  vector<SynonymRes> firstPKBResult = withEvaluatorFuncMap[firstEntityType]();
  IntermediateTable firstResult = IntermediateTableFactory::buildSingleColTable(
      firstSynonymValue, firstPKBResult);

  vector<SynonymRes> secondPKBResult = withEvaluatorFuncMap[secondEntityType]();
  IntermediateTable secondResult =
      IntermediateTableFactory::buildSingleColTable(secondSynonymValue,
                                                    secondPKBResult);

  // TODO(houten) integrate with yq for joining on specific attrref
  // return firstPKBResult.join(secondPKBResult, firstAttrRef, secondAttrRef)
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}
