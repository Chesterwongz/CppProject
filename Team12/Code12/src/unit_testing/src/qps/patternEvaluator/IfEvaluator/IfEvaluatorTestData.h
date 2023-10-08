#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../../mocks/MockContext.h"
#include "../../mocks/MockPKBReader.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/wildcard/Wildcard.h"

using std::unique_ptr, std::make_pair;

PKBStorage ifStorage = PKBStorage();

MockPKBReader ifMockPKBReader = MockPKBReader(ifStorage);

// for (test, _ , _)
vector<string> mockIfPatternStmtsSynonym = {"1", "2", "3"};

vector<string> mockIfPatternStmtsIdent = {"1"};  // for ("a", _ , _ )

vector<pair<string, string>> mockAllIfVariables = {
    make_pair("1", "a"),
    make_pair("2", "b"),
    make_pair("3", "c"),
};

MockContext ifMockContext = MockContext();

bool ifIsPartialMatchFalse = false;

string ifSynonymValue = "woof";
