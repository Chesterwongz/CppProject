#pragma once

#include <string>
#include <memory>
#include "assignEvaluator/AssignEvaluator.h"
#include "qps/context/Context.h"

using std::string, std::unique_ptr;

class PatternEvaluatorFactory {
public:
	static unique_ptr<AssignEvaluator> createAssignEvaluator(
		Context context, PatternArgsStreamPtr patternArgsStreamPtr, 
		PKBReader& pkbReader, bool isPartialMatch);
};