#include "TokenStream.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"

TokenStream::TokenStream(std::string fileContents, std::unique_ptr<ITokenHandler> tokenizerChain) {
    this->inputStream = std::make_shared<InputStream>(std::move(fileContents));
    this->tokenizerChain = std::move(tokenizerChain);
    // Prime the tokenizer with the first token
    this->lookAhead = nextToken();
}

std::optional<Token> TokenStream::nextToken() {
    inputStream->readWhile(StringUtils::isWhiteSpace); // Skip whitespaces

    if (inputStream->isEnd()) {
        return std::nullopt;
    }

    return tokenizerChain->tokenize(inputStream->peek(), inputStream);
}

std::optional<Token> TokenStream::peek() {
    return lookAhead;
}

std::optional<Token> TokenStream::eat() {
    std::optional<Token> currToken = this->lookAhead;
    this->lookAhead = nextToken();
    return currToken;
}
