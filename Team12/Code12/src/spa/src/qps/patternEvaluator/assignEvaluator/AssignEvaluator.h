#pragma once

#include "../IPatternEvaluator.h"

class AssignEvaluator : public IPatternEvaluator {
public:
	explicit AssignEvaluator(Context context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader& pkbReader, bool isPartialMatch) :
		IPatternEvaluator(context, std::move(patternArgsStreamPtr), pkbReader, isPartialMatch) {};

	QueryResult evaluate() override;
};
