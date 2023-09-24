#include "AssignEvaluator.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

IntermediateTable AssignEvaluator::evaluate() {
	PatternArgsStream patternArgsStream = std::move(*patternArgsStreamPtr);

	unique_ptr<IArgument> firstArg = std::move(patternArgsStream[0]);
	unique_ptr<IArgument> secondArg = std::move(patternArgsStream[1]);

	string firstArgValue = firstArg->getValue();

	bool isFirstArgSynonym = firstArg->isSynonym();

	string secondArgRPNValue = QPSStringUtils::convertToRPN(secondArg->getValue());

	vector<string> pkbResult;

	if (isPartialMatch) {
		pkbResult = pkbReader.getPartialAssignPattern(firstArgValue, secondArgRPNValue, isFirstArgSynonym);
	}
	else {
		pkbResult = pkbReader.getExactAssignPattern(firstArgValue, secondArgRPNValue, isFirstArgSynonym);
	}

	//vector<string> columnNames({firstArgValue});
	//vector<vector<string>> columns({ pkbResult });
	/*for (string element : pkbResult) {
		std::cout << element << " ";
	}
	std::cout << std::endl;*/
	return IntermediateTableFactory::buildSingleColTable(firstArgValue, pkbResult);
}
