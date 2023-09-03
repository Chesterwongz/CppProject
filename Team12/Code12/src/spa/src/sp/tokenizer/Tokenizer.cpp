#include "Tokenizer.h"
#include "sp/tokenizer/handlers/NameTokenHandler.h"

Tokenizer::Tokenizer(string &fileContents) {
    tokenStream = std::make_shared<TokenStream>(fileContents);
    // Add handlers here
    std::unique_ptr<ITokenHandler> nameTokenHandler = std::make_unique<NameTokenHandler>();
    std::unique_ptr<ITokenHandler> integerTokenHandler = std::make_unique<ConstTokenHandler>();
    // Construct pipeline
    nameTokenHandler->setNext(std::move(integerTokenHandler));
    handlerPipeline = std::move(nameTokenHandler);
}

std::optional<Token> Tokenizer::nextToken() {
    tokenStream->readWhile(StringUtils::isWhiteSpace); // Skip whitespaces

    if (!tokenStream->hasMoreTokens()) {
        return std::nullopt;
    }

    return handlerPipeline->handle(tokenStream);
}
