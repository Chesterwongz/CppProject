#include "AssignEvaluator.h"
#include "../../argument/IArgument.h"
#include "../../common/QPSStringUtils.h"

QueryResult AssignEvaluator::evaluate() {
	PatternArgsStream patternArgsStream = *patternArgsStreamPtr;

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	string firstArgValue;
	
	if (firstArg->isSynonym()) {
		firstArgValue = QPSStringUtils::WILDCARD;
	}
	else {
		firstArgValue = firstArg->getValue();
	}

	string secondArgRPNValue = QPSStringUtils::convertToRPN(secondArg->getValue());

	vector<string> pkbResult = pkbReader->getExactPattern(firstArgValue, secondArgRPNValue);

	//TODO: make intermediate table.

	// pkbReader->getAssignPattern(firstArg, secondArgRPNValue);
}
