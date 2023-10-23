#include "SpNameTokenizer.h"

SpToken SpNameTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!StringUtils::isAlpha(nextCh)) {  // filter non-alphabets
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  return {SpTokenType::NAME,
          inputStream.readWhile(StringUtils::isAlphaNumeric)};
}
