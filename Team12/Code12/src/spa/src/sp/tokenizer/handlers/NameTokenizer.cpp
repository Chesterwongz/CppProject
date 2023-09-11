#include "NameTokenizer.h"

Token NameTokenizer::tokenize(char nextCh, std::shared_ptr<InputStream> tokenStream) {
    if (!StringUtils::isAlpha(nextCh)) { // filter non-alphabets
        return BaseTokenizer::tokenize(nextCh, tokenStream);
    }

    return {TokenType::NAME, tokenStream->readWhile(StringUtils::isAlphaNumeric)};
}
