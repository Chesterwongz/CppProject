#include "AssignEvaluator.h"
#include "../../argument/IArgument.h"
#include "../../common/QPSStringUtils.h"

std::set<string> AssignEvaluator::evaluate() {
	PatternArgsStream patternArgsStream = *patternArgsStreamPtr;

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	string firstArgValue = firstArg->getValue();
	string secondArgRPNValue = QPSStringUtils::convertToRPN(secondArg->getValue());
	// TODO: call PKB

	// pkbReader->getAssignPattern(firstArg, secondArgRPNValue);
}
