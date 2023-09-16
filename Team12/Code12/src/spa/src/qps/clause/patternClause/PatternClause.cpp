#include "PatternClause.h"
#include "../../patternEvaluator/PatternEvaluatorFactory.h"
#include "../../patternEvaluator/IPatternEvaluator.h"
#include <utility>

PatternClause::PatternClause(unique_ptr<IArgument> synonym, PatternArgsStreamPtr patternArgsStreamPtr) {
	PatternClause::synonym = std::move(synonym);
	PatternClause::patternArgsStreamPtr = std::move(patternArgsStreamPtr);
}


//prolly will change method return type to set<string>
QueryResult PatternClause::evaluate(Context context, PKBReader* pkbReader, string& synonymToQuery) {
	string synonymValue = synonym->getValue();
	string entityType = context.getTokenEntity(synonymValue);

	unique_ptr<IPatternEvaluator> IEvaluatorPtr;

	if (entityType == PATTERN_ASSIGN_TYPE) {
		IEvaluatorPtr =  PatternEvaluatorFactory::createAssignEvaluator(context, std::move(patternArgsStreamPtr), pkbReader);
	}

	return IEvaluatorPtr->evaluate();
	//return std::unordered_set<int>();
}
