#include "PatternClause.h"
#include "qps/common/Keywords.h"

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

	if (entityType == ASSIGN_ENTITY) {
		IEvaluatorPtr =  PatternEvaluatorFactory::createAssignEvaluator(
				context,
				std::move(patternArgsStreamPtr),
				pkbReader,
				isPartialMatch,
				synonymValue);
	}

	return IEvaluatorPtr->evaluate();
}

bool PatternClause::isEquals(const Clause& other) {
    const auto* otherPattern = dynamic_cast<const PatternClause*>(&other);
    if (!otherPattern) return false;

    for (int i = 0; i < patternArgsStreamPtr->size(); ++i) {
        if (!(*patternArgsStreamPtr->at(i) == *otherPattern->patternArgsStreamPtr->at(i))) {
            return false;
        }
    }
    return isPartialMatch == otherPattern->isPartialMatch
           && *synonym == *otherPattern->synonym;
}
