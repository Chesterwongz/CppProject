#include "SpIntegerTokenizer.h"

SpToken SpIntegerTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!StringUtils::isDigit(nextCh)) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }
  const std::string value = inputStream.readWhile(StringUtils::isDigit);

  // Const cannot start with zero
  if (value.length() > 1 && value[0] == StringUtils::CHAR_ZERO) {
    throw SyntaxError(value);
  }
  return {SpTokenType::INT, value};
}
