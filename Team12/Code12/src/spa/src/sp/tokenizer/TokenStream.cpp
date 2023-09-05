#include "TokenStream.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"

Tokenizer::Tokenizer(string &fileContents) {
    inputStream = std::make_shared<InputStream>(fileContents);
    // Add handlers here
    std::unique_ptr<ITokenizer> nameTokenizer = std::make_unique<NameTokenizer>();
    std::unique_ptr<ITokenizer> integerTokenizer = std::make_unique<IntegerTokenizer>();
    // Construct pipeline
    nameTokenizer->setNext(std::move(integerTokenizer));
    handlerPipeline = std::move(nameTokenizer);

    // Prime the tokenizer with the first token
    lookAhead = nextToken();
}

std::optional<Token> Tokenizer::nextToken() {
    inputStream->readWhile(StringUtils::isWhiteSpace); // Skip whitespaces

    if (inputStream->isEnd()) {
        return std::nullopt;
    }

    return handlerPipeline->tokenize(inputStream->peek(), inputStream);
}

std::optional<Token> Tokenizer::peek() {
    return lookAhead;
}

std::optional<Token> Tokenizer::eat() {
    std::optional<Token> currToken = this->lookAhead;
    this->lookAhead = nextToken();
    return currToken;
}
