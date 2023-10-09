#include "PQLLiteralTokenizer.h"

PQLToken PQLLiteralTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (nextCh != pqlDelim::kQuoteChar) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  inputStream.read(); // get rid of the first quote
  string literal = inputStream.readWhile(QPSStringUtils::isNotQuoteEnd);
  inputStream.read(); // get rid of the last quote

  string trimmed = QPSStringUtils::trimString(std::move(literal));

  PQLTokenType type = QPSStringUtils::hasMoreThanOneWord(trimmed)
                          ? PQLTokenType::PQL_LITERAL_EXPRESSION_TOKEN
                          : PQLTokenType::PQL_LITERAL_REF_TOKEN;

  return {type, trimmed};
}
