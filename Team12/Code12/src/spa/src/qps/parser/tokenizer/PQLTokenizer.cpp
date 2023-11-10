#include "PQLTokenizer.h"

std::unique_ptr<TokenStream<PQLToken>> PQLTokenizer::tokenize(
    std::string query) {
  std::unique_ptr<ITokenHandler<PQLToken>> pqlTokenizer =
      std::make_unique<PQLTokenHandler>();

  InputStream inputStream = InputStream(std::move(query));
  return TokenStream<PQLToken>::initialize(inputStream, *pqlTokenizer);
}
