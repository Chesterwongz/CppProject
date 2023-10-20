#include "PQLNameTokenizer.h"

PQLToken PQLNameTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!StringUtils::isAlpha(nextCh)) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  return {PQLTokenType::PQL_NAME_TOKEN,
          inputStream.readWhile(QPSStringUtils::isNameTokenChar)};
}
