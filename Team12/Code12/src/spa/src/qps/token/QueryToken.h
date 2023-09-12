#pragma once

#include <string>
#include <vector>
#include <memory>

#include "qps/clause/Clause.h"

using std::string;

class QueryToken {
public:
    virtual std::unique_ptr<Clause> buildClause() = 0;
    virtual ~QueryToken() = default;
};

// TODO: feels like should be moved to a separate folder for references in the future
enum Reference {
    WILDCARD,
    SYNONYM,
    STRING,
    LINE_NUMBER
};

typedef std::string Synonym;
