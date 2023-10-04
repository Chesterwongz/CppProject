#pragma once

#include "../../mocks/MockContext.h"
#include "../../mocks/MockPKBReader.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"

using std::unique_ptr, std::make_pair;

PKBStorage storage = PKBStorage();

MockPKBReader mockPKBReader = MockPKBReader(storage);

vector<string> mockIfPatternStmtsSynonym = { "1", "2", "3" };	// for (test, _ , _)

vector<string> mockIfPatternStmtsIdent = { "1" };     // for ("a", _ , _ )

vector<pair<string, string>> mockAllIfVariables = {
	make_pair("1", "a"),
	make_pair("2", "b"),
	make_pair("3", "c"),
	make_pair("4", "d"),
	make_pair("5", "e"),
};

MockContext mockContext = MockContext();

bool isPartialMatchFalse = false;

string synonymValue = "woof";
