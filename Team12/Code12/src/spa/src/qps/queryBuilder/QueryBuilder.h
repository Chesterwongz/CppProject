#pragma once

#include <memory>

#include "pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/QueryToken.h"
#include "qps/tokenFactory/TokenFactory.h"
#include "qps/context/Context.h"

using std::unique_ptr;

class QueryBuilder {
private:
    unique_ptr<PKBReader>& pkbReader;
    unique_ptr<Context>& synonymTable;

public:
    explicit QueryBuilder(unique_ptr<PKBReader>& pkb);
    Query buildQuery(QPSTokenStream& queryTokenVector);

};
