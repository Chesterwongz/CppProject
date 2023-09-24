#pragma once

#include "../mocks/MockPKBReader.h"
#include "../mocks/MockContext.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"

using std::unique_ptr;

PKBStorage storage = PKBStorage();

MockPKBReader mockPKBReader = MockPKBReader(storage);

vector<string> mockExactAssignPatternStmts = {"1", "2", "3"};

MockContext mockContext = MockContext();

//PatternArgsStream patternArgsStreamtest = std::make_unique<PatternArgsStream>(std::move(patternArgsStreamTest));

bool isPartialMatchFalse = false;


