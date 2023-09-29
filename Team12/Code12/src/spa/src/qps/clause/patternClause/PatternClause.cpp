#include "PatternClause.h"

IntermediateTable PatternClause::evaluate(Context& context,
										  PKBReader& pkbReader) {
	string synonymValue = synonym->getValue();
	string entityType = context.getTokenEntity(synonymValue);

	unique_ptr<IPatternEvaluator> IEvaluatorPtr;


	IEvaluatorPtr =  PatternEvaluatorFactory::createEvaluator(
			entityType,
			context,
			*patternArgsStreamPtr,
			pkbReader,
			isPartialMatch,
			synonymValue);


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
