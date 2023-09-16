#include "AssignEvaluator.h"
#include "../../argument/IArgument.h"

std::set<string> AssignEvaluator::evaluate() {
	// TODO: shunting yard algo
	PatternArgsStream patternArgsStream = *patternArgsStreamPtr;

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	
	// TODO: call PKB

	// pkbReader->getAssignPattern(firstArg, secondArg);
}