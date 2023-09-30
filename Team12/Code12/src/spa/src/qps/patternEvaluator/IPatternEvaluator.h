#pragma once 

#include <string>
#include <vector>
#include <memory>
#include <set>
#include "qps/context/Context.h"
#include "qps/argument/AbstractArgument.h"
#include "pkb/facade/PKBReader.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set;

typedef vector<unique_ptr<AbstractArgument>> PatternArgsStream;

class IPatternEvaluator {
protected:
	Context& context;
	PatternArgsStream& patternArgsStream;
	PKBReader& pkbReader;
	bool isPartialMatch;
	string synonymValue;
public:
	explicit IPatternEvaluator(
			Context& context,
			PatternArgsStream& patternArgsStream,
			PKBReader& pkbReader,
			bool isPartialMatch,
			string synonymValue) :
		context(context),
		patternArgsStream(patternArgsStream),
		pkbReader(pkbReader),
		isPartialMatch(isPartialMatch),
		synonymValue(synonymValue) {};
    virtual ~IPatternEvaluator() = default;
	virtual IntermediateTable evaluate() = 0;
};
