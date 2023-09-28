#include "PatternEvaluatorFactory.h"

unique_ptr<IPatternEvaluator> PatternEvaluatorFactory::createEvaluator(
	string& entityType, Context& context, PatternArgsStream& patternArgsStream, PKBReader& pkbReader, bool isPartialMatch, string synonymValue) {

	if (entityType == ASSIGN_ENTITY) {
		return createAssignEvaluator(
			context,
			patternArgsStream,
			pkbReader,
			isPartialMatch,
			synonymValue);
	}
	
	return nullptr;
}

unique_ptr<AssignEvaluator> PatternEvaluatorFactory::createAssignEvaluator(
	Context& context, PatternArgsStream& patternArgsStream, PKBReader& pkbReader, bool isPartialMatch, string synonymValue) {
	
	return std::make_unique<AssignEvaluator>(context, patternArgsStream, pkbReader, isPartialMatch, synonymValue);
}
