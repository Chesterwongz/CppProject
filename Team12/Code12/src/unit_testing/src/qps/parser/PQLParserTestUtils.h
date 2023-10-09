#pragma once

#include <memory>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"

extern PKBStorage dummyQpsParserStorage;
extern PKBReader dummyQpsParserPkbReader;

std::unique_ptr<Query> parseToQuery(std::vector<PQLToken> tokenList,
                                    PKBReader& pkbReader);
