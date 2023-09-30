#pragma once

#include <string>
#include <memory>
#include "assignEvaluator/AssignEvaluator.h"
#include "qps/context/Context.h"
#include "qps/common/Keywords.h"

using std::string, std::unique_ptr;

class PatternEvaluatorFactory {
public:
	static unique_ptr<IPatternEvaluator> createEvaluator(
		string& entityType,
		Context& context,
		PatternArgsStream& patternArgsStream,
		PKBReader& pkbReader,
		bool isPartialMatch,
		string synonymValue
	);
	
};
