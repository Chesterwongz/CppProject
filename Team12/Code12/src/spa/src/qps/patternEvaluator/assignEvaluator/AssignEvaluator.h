#pragma once

#include "qps/patternEvaluator/IPatternEvaluator.h"

class AssignEvaluator : public IPatternEvaluator {
public:
	explicit AssignEvaluator(Context context,
							 PatternArgsStreamPtr patternArgsStreamPtr,
							 PKBReader& pkbReader,
							 bool isPartialMatch) :
							 IPatternEvaluator(context,
											   std::move(patternArgsStreamPtr),
											   pkbReader,
											   isPartialMatch) {};
    ~AssignEvaluator() override = default;
	IntermediateTable evaluate() override;
};
