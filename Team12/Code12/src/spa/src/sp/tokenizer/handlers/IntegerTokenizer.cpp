#include "IntegerTokenizer.h"

Token IntegerTokenizer::tokenize(char nextCh, std::shared_ptr<InputStream> tokenStream) {
    if (!StringUtils::isDigit(nextCh)) {
        return BaseTokenizer::tokenize(nextCh, tokenStream);
    }
    const std::string value = tokenStream->readWhile(StringUtils::isDigit);

    // Const cannot start with zero
    if (value.length() > 1 && value[0] == StringUtils::CHAR_ZERO) {
        throw SyntaxError(StringUtils::CHAR_ZERO);
    }
    return {TokenType::INT, value};
}
