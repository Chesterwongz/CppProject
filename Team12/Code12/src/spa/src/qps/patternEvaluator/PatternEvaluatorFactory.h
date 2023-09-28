#pragma once

#include <string>
#include <memory>
#include "assignEvaluator/AssignEvaluator.h"
#include "qps/context/Context.h"
#include "qps/common/Keywords.h"

using std::string, std::unique_ptr;

class PatternEvaluatorFactory {
private:
	static unique_ptr<AssignEvaluator> createAssignEvaluator(
		Context context,
		PatternArgsStreamPtr patternArgsStreamPtr,
		PKBReader& pkbReader,
		bool isPartialMatch,
		string synonymValue);
public:
	static unique_ptr<IPatternEvaluator> createEvaluator(
		string entityType,
		Context context,
		PatternArgsStreamPtr patternArgsStreamPtr,
		PKBReader& pkbReader,
		bool isPartialMatch,
		string synonymValue
	);
	
};
