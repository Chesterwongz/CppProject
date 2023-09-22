#pragma once 

#include <string>
#include <vector>
#include <memory>
#include <set>
#include "../context/Context.h"
#include "qps/argument/IArgument.h"
#include "pkb/facade/PKBReader.h"

using std::string, std::vector, std::unique_ptr, std::set;

typedef vector<unique_ptr<IArgument>> PatternArgsStream;
typedef unique_ptr<PatternArgsStream> PatternArgsStreamPtr;
typedef string StmtSynonym;
typedef set<string> PossibleValues;
typedef map<StmtSynonym, PossibleValues > QueryResult;


class IPatternEvaluator {
protected:
	Context context;
	PatternArgsStreamPtr patternArgsStreamPtr;
	PKBReader& pkbReader;
	bool isPartialMatch;
public:
	explicit IPatternEvaluator(Context context, PatternArgsStreamPtr patternArgsStreamPtr, PKBReader& pkbReader, bool isPartialMatch) :
		context(context),
		patternArgsStreamPtr(std::move(patternArgsStreamPtr)),
		pkbReader(pkbReader),
		isPartialMatch(isPartialMatch) {};

	virtual QueryResult evaluate() = 0;
};
