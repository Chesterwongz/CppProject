#include "PQLTokenHandler.h"

PQLToken PQLTokenHandler::tokenize(char nextCh, InputStream &inputStream) {
  if (StringUtils::isAlpha(nextCh)) {  // NameTokenizer
    return processNameToken(inputStream);
  } else if (StringUtils::isDigit(nextCh)) {  // IntegerTokenizer
    return processIntegerToken(inputStream);
  } else if (nextCh == pqlDelim::kQuoteChar) {  // LiteralTokenizer
    return processLiteralToken(inputStream);
  } else if (PQLParserUtils::isDelimiter(nextCh)) {  // DelimiterTokenizer
    return processDelimiterToken(nextCh, inputStream);
  } else {
    throw CommonSyntaxError(std::string(1, nextCh));
  }
}

PQLToken PQLTokenHandler::processNameToken(InputStream &inputStream) {
  return {PQLTokenType::PQL_NAME_TOKEN,
          inputStream.readWhile(QPSStringUtils::isNameTokenChar)};
}

PQLToken PQLTokenHandler::processIntegerToken(InputStream &inputStream) {
  const std::string value = inputStream.readWhile(StringUtils::isAlphaNumeric);

  if (!QPSStringUtils::isInteger(value)) {
    throw CommonSyntaxError(value);
  }

  return {PQLTokenType::PQL_INTEGER_TOKEN, value};
}

PQLToken PQLTokenHandler::processLiteralToken(InputStream &inputStream) {
  inputStream.read();  // remove start quotation marks
  string literal = inputStream.readWhile(QPSStringUtils::isNotQuoteEnd);

  if (inputStream.isEnd()) {
    throw CommonSyntaxError(QPS_TOKENIZATION_ERR_UNMATCHED_QUOTE);
  }
  inputStream.read();  // remove end quotation marks

  if (literal.empty()) {
    throw CommonSyntaxError(QPS_TOKENIZATION_ERR_EMPTY_QUOTE);
  }
  QPSStringUtils::trimString(literal);

  PQLTokenType type = QPSStringUtils::isIdent(literal)
                          ? PQLTokenType::PQL_LITERAL_REF_TOKEN
                          : PQLTokenType::PQL_LITERAL_REF_TOKEN;
  return {type, literal};
}

PQLToken PQLTokenHandler::processDelimiterToken(char nextCh,
                                                InputStream &inputStream) {
  PQLTokenType type = PQLParserUtils::isDelimiterToken(nextCh);
  return {type, inputStream.read()};
}
