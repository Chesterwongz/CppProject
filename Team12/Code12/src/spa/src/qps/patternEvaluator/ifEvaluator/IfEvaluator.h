#pragma once

#include "qps/patternEvaluator/PatternEvaluator.h"

class IfEvaluator : public PatternEvaluator {
public:
	explicit IfEvaluator(Context& context,
		PatternArgsStream& patternArgsStream,
		PKBReader& pkbReader,
		bool isPartialMatch,
		string synonymValue) :
		PatternEvaluator(context,
			patternArgsStream,
			pkbReader,
			isPartialMatch,
			synonymValue) {};
	~IfEvaluator() override = default;
	vector<string> processArguments() override;
};
