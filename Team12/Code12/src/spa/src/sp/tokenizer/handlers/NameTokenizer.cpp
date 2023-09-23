#include "NameTokenizer.h"

Token NameTokenizer::tokenize(char nextCh, InputStream &inputStream) {
    if (!StringUtils::isAlpha(nextCh)) { // filter non-alphabets
        return BaseTokenizer::tokenize(nextCh, inputStream);
    }

    return {TokenType::NAME, inputStream.readWhile(StringUtils::isAlphaNumeric)};
}
