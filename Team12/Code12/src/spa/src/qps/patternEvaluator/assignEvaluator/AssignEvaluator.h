#pragma once

#include "qps/patternEvaluator/IPatternEvaluator.h"

class AssignEvaluator : public IPatternEvaluator {
public:
	explicit AssignEvaluator(Context& context,
							 PatternArgsStream& patternArgsStream,
							 PKBReader& pkbReader,
							 bool isPartialMatch,
							 string synonymValue) :
							 IPatternEvaluator(context,
											   patternArgsStream,
											   pkbReader,
											   isPartialMatch,
											   synonymValue) {};
    ~AssignEvaluator() override = default;
	IntermediateTable evaluate() override;
};
