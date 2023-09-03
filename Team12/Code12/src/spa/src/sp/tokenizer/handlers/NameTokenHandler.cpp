#include "NameTokenHandler.h"

Token NameTokenHandler::handle(std::shared_ptr<TokenStream> tokenStream) {
    const char ch = tokenStream->peek();

    if (!StringUtils::isAlpha(ch)) { // filter non-alphabets
        return BaseTokenHandler::handle(tokenStream);
    }

    return {TokenType::NAME, tokenStream->readWhile(StringUtils::isAlphaNumeric)};
}
