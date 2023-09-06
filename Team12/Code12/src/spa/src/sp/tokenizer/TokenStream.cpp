#include "TokenStream.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"

TokenStream::TokenStream(string &fileContents, std::unique_ptr<ITokenizer> tokenizerPipeline) {
    inputStream = std::make_shared<InputStream>(fileContents);


    // Prime the tokenizer with the first token
    lookAhead = nextToken();
}

std::optional<Token> TokenStream::nextToken() {
    inputStream->readWhile(StringUtils::isWhiteSpace); // Skip whitespaces

    if (inputStream->isEnd()) {
        return std::nullopt;
    }

    return handlerPipeline->tokenize(inputStream->peek(), inputStream);
}

std::optional<Token> TokenStream::peek() {
    return lookAhead;
}

std::optional<Token> TokenStream::eat() {
    std::optional<Token> currToken = this->lookAhead;
    this->lookAhead = nextToken();
    return currToken;
}
