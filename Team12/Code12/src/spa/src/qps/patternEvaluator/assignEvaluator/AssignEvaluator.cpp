#include "AssignEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

IntermediateTable AssignEvaluator::evaluate() {
	PatternArgsStream patternArgsStream = std::move(*patternArgsStreamPtr);

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	string firstArgValue = firstArg->getValue();

	bool isFirstArgSynonym = firstArg->isSynonym();

	string secondArgRPNValue;

	if (secondArg->isWildcard()) {
		secondArgRPNValue = secondArg->getValue();
	}
	else {
		secondArgRPNValue = QPSStringUtils::convertToRPN(secondArg->getValue());
	}

	vector<string> pkbResult;

	if (isPartialMatch) {
		pkbResult = pkbReader.getPartialAssignPattern(firstArgValue, secondArgRPNValue, isFirstArgSynonym);
	}
	else {
		pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgRPNValue, isFirstArgSynonym);
	}

	IntermediateTable tmp = IntermediateTableFactory::buildSingleColTable("line", pkbResult);
	vector<pair<string, string>> lineVariablePairs = pkbReader.getAllModifiedVariables(StmtType::ASSIGN);
	IntermediateTable tmp2 = IntermediateTableFactory::buildIntermediateTable("line", firstArgValue, lineVariablePairs);
	return tmp.join(tmp2);
}
