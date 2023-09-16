#include "PatternEvaluatorFactory.h"

unique_ptr<AssignEvaluator> PatternEvaluatorFactory::createAssignEvaluator(
	Context context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader* pkbReader) {
	
	return std::make_unique<AssignEvaluator>(context, std::move(patternArgsStreamPtr), pkbReader);
}