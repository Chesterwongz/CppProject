#include <utility>
#include <vector>
#include <memory>
#include <algorithm>

#include "qps/exceptions/QpsException.h"
#include "QPS.h"

using std::string, std::vector, std::unique_ptr;

QPS::QPS(PKBReader& pkb, const string& query) :
    pkb(pkb),
    tokenizer(PQLTokenizer(query)) {}


