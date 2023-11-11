#include "PQLIntegerTokenizer.h"

PQLToken PQLIntegerTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!StringUtils::isDigit(nextCh)) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }
  const std::string value = inputStream.readWhile(StringUtils::isAlphaNumeric);

  if (!QPSStringUtils::isInteger(value)) {
    throw CommonSyntaxError(
        value);  //  to be consistent with SpIntegerTokenizer
  }

  return {PQLTokenType::PQL_INTEGER_TOKEN, value};
}
