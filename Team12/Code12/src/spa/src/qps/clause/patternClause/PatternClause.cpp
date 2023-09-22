#include "PatternClause.h"

PatternClause::PatternClause(unique_ptr<IArgument> synonym, PatternArgsStreamPtr patternArgsStreamPtr, bool isPartialMatch) {
	PatternClause::synonym = std::move(synonym);
	PatternClause::patternArgsStreamPtr = std::move(patternArgsStreamPtr);
	PatternClause::isPartialMatch = isPartialMatch;
}


//prolly will change method return type to set<string>
QueryResult PatternClause::evaluate(Context context, PKBReader& pkbReader, string& synonymToQuery) {
	string synonymValue = synonym->getValue();
	string entityType = context.getTokenEntity(synonymValue);

	unique_ptr<IPatternEvaluator> IEvaluatorPtr;

	if (entityType == PATTERN_ASSIGN_TYPE) {
		IEvaluatorPtr =  PatternEvaluatorFactory::createAssignEvaluator(context, std::move(patternArgsStreamPtr), pkbReader, isPartialMatch);
	}

	return IEvaluatorPtr->evaluate();
	//return std::unordered_set<int>();
}
