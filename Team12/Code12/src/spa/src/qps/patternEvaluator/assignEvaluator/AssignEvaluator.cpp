#include "AssignEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

IntermediateTable AssignEvaluator::evaluate() {
	PatternArgsStream patternArgsStream = std::move(*patternArgsStreamPtr);

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	string firstArgValue;

	if (firstArg->isSynonym()) {
		firstArgValue = WILDCARD_KEYWORD;
	}
	else {
		firstArgValue = firstArg->getValue();
	}

	string secondArgRPNValue = QPSStringUtils::convertToRPN(secondArg->getValue());

	vector<string> pkbResult;

	if (isPartialMatch) {
		pkbResult = pkbReader.getPartialAssignPattern(firstArgValue, secondArgRPNValue);
	}
	else {
		pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgRPNValue);
	}

	vector<string> columnNames({firstArgValue});
	vector<vector<string>> columns({ pkbResult });
	return IntermediateTableFactory::buildIntermediateTable(columnNames, columns);
}
