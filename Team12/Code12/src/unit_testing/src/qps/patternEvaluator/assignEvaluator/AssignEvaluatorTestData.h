#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../mocks/MockContext.h"
#include "../../mocks/MockPKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"

using std::unique_ptr, std::make_pair;

PKBStorage storage = PKBStorage();

MockPKBReader mockPKBReader = MockPKBReader(storage);

vector<string> mockExactAssignPatternStmts = {"1", "2", "3"};

vector<string> mockExactAssignPatternStmtsIdent = {"1"};

vector<pair<string, string>> mockAllModifiedVariables = {
    make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c"),
    make_pair("4", "d"), make_pair("5", "e"),
};

MockContext mockContext = MockContext();

bool isPartialMatchFalse = false;

string synonymValue = "meow";
