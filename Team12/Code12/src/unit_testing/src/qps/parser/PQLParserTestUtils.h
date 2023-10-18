#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

extern PKBStorage dummyQpsParserStorage;
extern PKBReader dummyQpsParserPkbReader;

std::unique_ptr<Query> parseToQuery(std::vector<PQLToken> tokenList,
                                    PKBReader& pkbReader);

std::unique_ptr<Query> parseStringToQuery(const string& query,
                                          PKBReader& pkbReader);
