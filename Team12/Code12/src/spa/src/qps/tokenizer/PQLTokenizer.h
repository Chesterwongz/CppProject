#pragma once

#include <string>
#include <memory>

#include "tokenStream/PQLTokenStream.h"
#include "PQLTokenTable.h"

using std::string, std::unique_ptr, std::make_unique;

class PQLTokenizer {
private:
    PQLTokenType currType;
    string buffer;
    TokenPtrList* tokenList;
    PQLTokenTable* tokenTable;
    bool processingLiteral;
    bool processingArgument; // values between brackets

    void processChar(const char c);
    void toggleLiteral();
    void flushBuffer();
    void appendToken(PQLToken* token);

public:
    explicit PQLTokenizer();
    // TokenStream is owned by QPS driver which will pass the token stream for predictive parsing 
    unique_ptr<PQLTokenStream> tokenize(const string &query);
};
