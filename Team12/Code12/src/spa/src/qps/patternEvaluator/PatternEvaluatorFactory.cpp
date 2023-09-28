#include "PatternEvaluatorFactory.h"

unique_ptr<IPatternEvaluator> PatternEvaluatorFactory::createEvaluator(
	string& entityType, Context& context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader& pkbReader, bool isPartialMatch, string synonymValue) {

	if (entityType == ASSIGN_ENTITY) {
		return createAssignEvaluator(
			context,
			std::move(patternArgsStreamPtr),
			pkbReader,
			isPartialMatch,
			synonymValue);
	}
	
	return nullptr;
}

unique_ptr<AssignEvaluator> PatternEvaluatorFactory::createAssignEvaluator(
	Context& context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader& pkbReader, bool isPartialMatch, string synonymValue) {
	
	return std::make_unique<AssignEvaluator>(context, std::move(patternArgsStreamPtr), pkbReader, isPartialMatch, synonymValue);
}
