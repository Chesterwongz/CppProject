#pragma once

#include <string>
#include <unordered_set>

#include "pkb/facade/PKBReader.h"
#include "qps/tokenizer/PQLTokenizer.h"

using std::string;

class QPS {
private:
    PKBReader &pkb;
    PQLTokenizer tokenizer;

public:
    explicit QPS(PKBReader &pkb, const string& query);
    std::set<string> processQueryString(string queryString);
};
