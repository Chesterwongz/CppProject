#pragma once

#include <string>
#include <memory>

#include "tokenStream/PQLTokenStream.h"
#include "PQLTokenTable.h"

using std::string, std::unique_ptr, std::make_unique, std::move;

class PQLTokenizer {
private:
    string buffer;
    string literalBuffer;
    unique_ptr<TokenPtrList> tokenList;
    PQLTokenTable* tokenTable;
    bool containsChar;
    bool processingLiteral;

    void processChar(const char c);
    void flushBuffer();

    void toggleLiteral();
    void startLiteral();
    void endLiteral();

public:
    explicit PQLTokenizer();
    // TokenStream is owned by QPS driver which will pass the token stream for predictive parsing 
    unique_ptr<PQLTokenStream> tokenize(const string &query);
};
