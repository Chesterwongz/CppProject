#include "ConstTokenHandler.h"

Token ConstTokenHandler::handle(std::shared_ptr<TokenStream> tokenStream) {
    const char ch = tokenStream->peek();
    if (!StringUtils::isDigit(ch)) {
        return BaseTokenHandler::handle(tokenStream);
    }
    const std::string value = tokenStream->readWhile(StringUtils::isDigit);

    // Const cannot start with zero
    if (value.length() > 1 && value[0] == StringUtils::CHAR_ZERO) {
        throw SyntaxError(StringUtils::CHAR_ZERO);
    }
    return {TokenType::INT, value};
}
