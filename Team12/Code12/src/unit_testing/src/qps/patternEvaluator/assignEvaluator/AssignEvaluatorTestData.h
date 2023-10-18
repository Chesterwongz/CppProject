#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../mocks/MockContext.h"
#include "../../mocks/MockPKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"

using std::unique_ptr, std::make_pair;

PKBStorage assignStorage = PKBStorage();

MockPKBReader assignMockPKBReader = MockPKBReader(assignStorage);

vector<pair<string, string>> mockExactAssignPatternStmts = {
    make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c")};

vector<pair<string, string>> mockExactAssignPatternStmtsIdent = {
    make_pair("1", "a")};

vector<pair<string, string>> mockAllModifiedVariables = {
    make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c"),
    make_pair("4", "d"), make_pair("5", "e"),
};

MockContext assignMockContext = MockContext();

bool assignIsPartialMatchFalse = false;

string assignSynonymValue = "meow";
