#pragma once

#include <string>
#include <unordered_set>

#include "pkb/facade/PKBReader.h"
#include "qps/tokenizer/PQLTokenizer.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/token/PQLToken.h"

using std::string;

class QPS {
private:
    PKBReader &pkb;
    PQLTokenizer tokenizer;
    void setupParser(PQLParserContext& pc);

public:
    explicit QPS(PKBReader &pkb, const string& query);
    std::set<string> processQueryString();
};
