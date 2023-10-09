#include "PQLDelimiterTokenizer.h"

PQLToken PQLDelimiterTokenizer::tokenize(char nextCh,
                                         InputStream &inputStream) {
  if (!isDelim(nextCh)) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }
  PQLTokenType type = delimiterToTokenType.find(nextCh)->second;
  return {type, std::string(1, nextCh)};
}

bool PQLDelimiterTokenizer::isDelim(const char ch) {
  return delimiterToTokenType.find(ch) != delimiterToTokenType.end();
}
