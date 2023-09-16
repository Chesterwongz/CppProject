#pragma once

#include "../IPatternEvaluator.h"

class AssignEvaluator : public IPatternEvaluator {
public:
	explicit AssignEvaluator(Context context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader* pkbReader) :
		IPatternEvaluator(context, std::move(patternArgsStreamPtr), pkbReader) {};

	std::set<string> evaluate() override;
};