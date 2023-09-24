#pragma once

#include "../../mocks/MockContext.h"
#include "../../mocks/MockPKBReader.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"

using std::unique_ptr;

PKBStorage storage = PKBStorage();

MockPKBReader mockPKBReader = MockPKBReader(storage);

vector<string> mockExactAssignPatternStmts = {"1", "2", "3"};

MockContext mockContext = MockContext();

bool isPartialMatchFalse = false;
