#include "TokenStream.h"


std::unique_ptr<TokenStream> TokenStream::initialize(std::string fileContents, ITokenHandler &tokenizerChain) {
    std::unique_ptr<TokenStream> tokenStream = std::make_unique<TokenStream>();
    InputStream inputStream = InputStream(std::move(fileContents));
    // Prime the tokenizer with the first token
    std::optional<Token> tokenOpt = nextToken(inputStream, tokenizerChain);
    tokenStream->currToken = tokenOpt;
    while (tokenOpt.has_value()) {
        tokenStream->tokenLst.push_back(tokenOpt.value());
        tokenOpt = nextToken(inputStream, tokenizerChain);
    }
    return tokenStream;
}

std::optional<Token> TokenStream::nextToken(InputStream &inputStream, ITokenHandler &tokenizerChain) {
    inputStream.readWhile(StringUtils::isWhiteSpace); // Skip whitespaces

    if (inputStream.isEnd()) {
        return std::nullopt;
    }

    return tokenizerChain.tokenize(inputStream.peek(), inputStream);
}

int TokenStream::getCursor() const {
    return cursor;
}

void TokenStream::setCursor(int n) {
    cursor = n;
    currToken = tokenLst[cursor];
}

std::optional<Token> TokenStream::peek() const {
    return currToken;
}

std::optional<Token> TokenStream::eat() {
    if (!currToken.has_value()) return currToken;

    std::optional<Token> temp = currToken;
    currToken = cursor + 1 < tokenLst.size() ? std::optional{tokenLst[++cursor]} : std::nullopt;
    return temp;
}
