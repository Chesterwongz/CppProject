#include "PQLDelimiterTokenizer.h"

PQLToken PQLDelimiterTokenizer::tokenize(char nextCh,
                                         InputStream &inputStream) {
  if (!PQLParserUtils::isDelimiter(nextCh)) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }
  PQLTokenType type = PQLParserUtils::isDelimiterToken(nextCh);
  return {type, inputStream.read()};
}
