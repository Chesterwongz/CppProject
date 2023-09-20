#pragma once

#include <string>
#include <memory>

#include "tokenStream/PQLTokenStream.h"
#include "PQLTokenTable.h"

using std::string, std::unique_ptr, std::make_unique, std::move;

static int BUFFER_SIZE = 2048;

class PQLTokenizer {
private:
    string buffer;
    string literalBuffer;
    unique_ptr<PQLTokenList> tokenList;
    int currPos;
    const string& query;
    bool isProcessingLiteral;
    int numberOfTokensInLiteral;

    PQLTokenTable tokenTable;

    void flushBuffer(PQLTokenType type);
    void flushLiteralBuffer(PQLTokenType type);

    void processName();
    void processInt();
    void processLiteral();
    void processSymbols(const PQLTokenType type);

public:
    explicit PQLTokenizer(const string& query);
    // TokenStream is owned by QPS driver which will pass the token stream for predictive parsing 
    unique_ptr<PQLTokenList> tokenize();
};
