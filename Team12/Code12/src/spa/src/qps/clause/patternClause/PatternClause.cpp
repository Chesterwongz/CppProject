#include "PatternClause.h"

PatternClause::PatternClause(unique_ptr<IArgument> synonym, PatternArgsStreamPtr patternArgsStreamPtr, bool isPartialMatch) {
	PatternClause::synonym = std::move(synonym);
	PatternClause::patternArgsStreamPtr = std::move(patternArgsStreamPtr);
	PatternClause::isPartialMatch = isPartialMatch;
}


IntermediateTable PatternClause::evaluate(Context& context,
										  PKBReader& pkbReader) {
	string synonymValue = synonym->getValue();
	string entityType = context.getTokenEntity(synonymValue);

	unique_ptr<IPatternEvaluator> IEvaluatorPtr;

	if (entityType == PATTERN_ASSIGN_TYPE) {
		IEvaluatorPtr =  PatternEvaluatorFactory::createAssignEvaluator(context, std::move(patternArgsStreamPtr), pkbReader, isPartialMatch);
	}

	return IEvaluatorPtr->evaluate();
}
