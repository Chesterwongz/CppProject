#pragma once 

#include <string>
#include <vector>
#include <memory>
#include <set>
#include "../context/Context.h"
#include "qps/argument/IArgument.h"
#include "pkb/facade/PKBReader.h"

using std::string, std::vector, std::unique_ptr;

typedef vector<unique_ptr<IArgument>> PatternArgsStream;
typedef unique_ptr<PatternArgsStream> PatternArgsStreamPtr;



class IPatternEvaluator {
protected:
	Context context;
	PatternArgsStreamPtr patternArgsStreamPtr;
	PKBReader* pkbReader;
public:
	explicit IPatternEvaluator(Context context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader* pkbReader) :
		context(context),
		patternArgsStreamPtr(std::move(patternArgsStreamPtr)),
		pkbReader(pkbReader) {};

	virtual std::set<string> evaluate() = 0;
};
