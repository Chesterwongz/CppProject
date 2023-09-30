#include "PatternEvaluatorFactory.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

unique_ptr<IPatternEvaluator> PatternEvaluatorFactory::createEvaluator(
	string& entityType, Context& context, PatternArgsStream& patternArgsStream, PKBReader& pkbReader, bool isPartialMatch, string synonymValue) {

	if (entityType == ASSIGN_ENTITY) {
		return std::make_unique<AssignEvaluator>(
			context, 
			patternArgsStream, 
			pkbReader, 
			isPartialMatch, 
			synonymValue
		);
	}
	
	throw QPSInvalidQueryException("Unable to create PatternEvaluator of type: " + entityType);
}
