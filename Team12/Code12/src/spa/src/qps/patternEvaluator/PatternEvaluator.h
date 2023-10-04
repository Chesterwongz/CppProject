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

class PatternEvaluator {
protected:
	Context& context;
	PatternArgsStream& patternArgsStream;
	PKBReader& pkbReader;
	bool isPartialMatch;
	string synonymValue;
public:
	explicit PatternEvaluator(
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
	virtual IntermediateTable evaluate();
	virtual IntermediateTable buildResultTable(vector<string> pkbResult);
	virtual vector<string> processArguments() = 0;
    virtual ~PatternEvaluator() = default;
};
