//#include <vector>
//
//#include "qps/clause/utils/ClauseConstants.h"
//#include "qps/intermediateTable/IntermediateTableFactory.h"
//#include "qps/withEvaluator/doubleSynWithEvaluator/DoubleSynWithEvaluator.h"
//
//IntermediateTable DoubleSynWithEvaluator::evaluate(PKBReader& pkbReader) {
//  Entity firstEntityType = firstSynonymArg->getEntityType();
//  AttrRef firstAttrRef = firstSynonymArg->getAttrRef();
//
//  Entity secondEntityType = secondSynonymArg->getEntityType();
//  AttrRef secondAttrRef = secondSynonymArg->getAttrRef();
//
//  Entity_AttrRef_Permutation firstArgPermutation = getPermutation(
//      firstEntityType, firstAttrRef);
//
//  Entity_AttrRef_Permutation secondArgPermutation = getPermutation(
//      secondEntityType, secondAttrRef);
//
//  IntermediateTable firstPKBResult =
//      withEvaluatorFuncMap[firstArgPermutation](pkbReader);
//
//  IntermediateTable secondPKBResult =
//      withEvaluatorFuncMap[firstArgPermutation](pkbReader);
//  
//  // TODO(houten) integrate with yq for joining on specific attrref
//  // return firstPKBResult.join(secondPKBResult, firstAttrRef, secondAttrRef)
//  return IntermediateTableFactory::buildEmptyIntermediateTable();
//}
