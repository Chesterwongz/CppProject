#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

extern PKBReader dummyQpsParserPkbReader;

std::unique_ptr<Query> parseToQuery(const std::vector<PQLToken>& tokenList);

std::unique_ptr<Query> parseStringToQuery(const string& query);
