#include "PQLLiteralTokenizer.h"

PQLToken PQLLiteralTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (nextCh != pqlDelim::kQuoteChar) {
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  inputStream.read();  // get rid of the first quote
  string literal = inputStream.readWhile(QPSStringUtils::isNotQuoteEnd);

  if (inputStream.isEnd()) {
    throw CommonSyntaxError(QPS_TOKENIZATION_ERR_UNMATCHED_QUOTE);
  }
  inputStream.read();

  string trimmed = QPSStringUtils::trimString(std::move(literal));

  PQLTokenType type = QPSStringUtils::hasMoreThanOneWord(trimmed)
                          ? PQLTokenType::PQL_LITERAL_EXPRESSION_TOKEN
                          : PQLTokenType::PQL_LITERAL_REF_TOKEN;

  return {type, trimmed};
}
