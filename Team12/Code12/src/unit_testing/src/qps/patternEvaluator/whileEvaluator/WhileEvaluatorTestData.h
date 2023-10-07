#pragma once

#include "../../mocks/MockContext.h"
#include "../../mocks/MockPKBReader.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/wildcard/Wildcard.h"

using std::unique_ptr, std::make_pair;

PKBStorage whileStorage = PKBStorage();

MockPKBReader whileMockPKBReader = MockPKBReader(whileStorage);

vector<string> mockWhilePatternStmtsSynonym = 
                                 {"1", "2", "3"};  // for (test, _ , _)

vector<string> mockWhilePatternStmtsIdent = {"1"};  // for ("a", _ , _ )

vector<pair<string, string>> mockAllWhileVariables = {
    make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c")
};

MockContext whileMockContext = MockContext();

bool whileIsPartialMatchFalse = false;

string whileSynonymValue = "moo";
