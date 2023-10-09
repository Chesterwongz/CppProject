#include "PQLLiteralTokenizer.h"

PQLToken PQLLiteralTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (nextCh != pqlDelim::kQuoteChar) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  string literal = inputStream.readWhile(QPSStringUtils::isNotQuoteEnd);

  string trimmed = QPSStringUtils::trimString(std::move(literal));
  std::cout << "Literal: " << trimmed << std::endl;

  PQLTokenType type = QPSStringUtils::hasMoreThanOneWord(trimmed)
                          ? PQLTokenType::PQL_LITERAL_EXPRESSION_TOKEN
                          : PQLTokenType::PQL_LITERAL_REF_TOKEN;

  return {type, trimmed};
}
