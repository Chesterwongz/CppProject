#pragma once 

#include <string>
#include <vector>
#include <memory>
#include <set>
#include "qps/context/Context.h"
#include "qps/argument/IArgument.h"
#include "pkb/facade/PKBReader.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set;

typedef vector<unique_ptr<IArgument>> PatternArgsStream;
typedef unique_ptr<PatternArgsStream> PatternArgsStreamPtr;

class IPatternEvaluator {
protected:
	Context context;
	PatternArgsStreamPtr patternArgsStreamPtr;
	PKBReader& pkbReader;
	bool isPartialMatch;
public:
	explicit IPatternEvaluator(
			Context context,
			PatternArgsStreamPtr patternArgsStreamPtr,
			PKBReader& pkbReader,
			bool isPartialMatch) :
		context(context),
		patternArgsStreamPtr(std::move(patternArgsStreamPtr)),
		pkbReader(pkbReader),
		isPartialMatch(isPartialMatch) {};
    virtual ~IPatternEvaluator() = default;
	virtual IntermediateTable evaluate() = 0;
};
