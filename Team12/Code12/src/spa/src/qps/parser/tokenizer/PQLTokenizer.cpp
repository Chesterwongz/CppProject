#include "PQLTokenizer.h"

std::unique_ptr<TokenStream<PQLToken>> PQLTokenizer::tokenize(
    std::string query) {
  //  Language specifications
  std::unique_ptr<ITokenHandler<PQLToken>> nameTokenizer =
      std::make_unique<PQLNameTokenizer>();
  std::unique_ptr<ITokenHandler<PQLToken>> integerTokenizer =
      std::make_unique<PQLIntegerTokenizer>();
  std::unique_ptr<ITokenHandler<PQLToken>> literalTokenizer =
      std::make_unique<PQLLiteralTokenizer>();
  std::unique_ptr<ITokenHandler<PQLToken>> delimiterTokenizer =
      std::make_unique<PQLDelimiterTokenizer>();

  nameTokenizer->setNext(std::move(integerTokenizer))
      .setNext(std::move(literalTokenizer))
      .setNext(std::move(delimiterTokenizer));

  InputStream inputStream = InputStream(std::move(query));
  return TokenStream<PQLToken>::initialize(inputStream, *nameTokenizer);
}
