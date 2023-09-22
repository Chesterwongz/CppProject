#include "AssignEvaluator.h"
#include "../../argument/IArgument.h"
#include "../../common/QPSStringUtils.h"
#include "common/utils/StringUtils.h"

QueryResult AssignEvaluator::evaluate() {
	PatternArgsStream patternArgsStream = std::move(*patternArgsStreamPtr);

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	string firstArgValue;
	
	if (firstArg->isSynonym()) {
		firstArgValue = StringUtils::WILDCARD;
	}
	else {
		firstArgValue = firstArg->getValue();
	}

	string secondArgRPNValue = QPSStringUtils::convertToRPN(secondArg->getValue());

	vector<string> pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgRPNValue);

	//TODO: make intermediate table.

	// return intermediate table.
	return map<StmtSynonym, PossibleValues>(); //placeholder
}
