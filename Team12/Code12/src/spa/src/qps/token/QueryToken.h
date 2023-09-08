#pragma once

#include <string>
#include <vector>
#include "qps/clause/Clause.h"

class QueryToken;
typedef std::vector<QueryToken> TokenList;

class QueryToken {
public:
    static TokenList tokens;
    virtual bool semanticValidation() = 0;
    virtual Clause *buildClause() = 0;
};

//enum Entity {
//    PROCEDURE,
//    STATEMENT,
//    READ,
//    PRINT,
//    ASSIGN,
//    CALL,
//    WHILE,
//    IF,
//    VARIABLE,
//    CONSTANT
//};

// TODO: feels like should be moved to a separate folder for references in the future
enum Reference {
    WILDCARD,
    SYNONYM,
    STRING,
    LINE_NUMBER
};

typedef std::string Synonym;
