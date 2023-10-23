#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../../mocks/mockReaders/MockPatternsReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"

using std::unique_ptr, std::make_pair;

MockPatternsReader whileMockPKBReader = MockPatternsReader();

// for (test, _ , _)
vector<pair<string, string>> mockWhilePatternStmtsSynonym = {
    make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c")};

vector<pair<string, string>> mockWhilePatternStmtsIdent = {
    make_pair("1", "a")};  // for ("a", _ , _ )

vector<pair<string, string>> mockAllWhileVariables = {
    make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c")};

bool whileIsPartialMatchFalse = false;

string whileSynonymValue = "moo";
