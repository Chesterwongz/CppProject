#include "PQLParserTestUtils.h"

PKBStorage dummyQpsParserStorage{};
PKBReader dummyQpsParserPkbReader(dummyQpsParserStorage);

std::unique_ptr<Query> parseToQuery(std::vector<PQLToken> tokenList,
                                    PKBReader& pkbReader) {
  std::unique_ptr<PQLTokenStream> tokenStreamPtr =
      std::make_unique<PQLTokenStream>(tokenList);

  std::unique_ptr<Query> query = std::make_unique<Query>(pkbReader);

  PQLParserContext parserContext(std::move(tokenStreamPtr), query);
  std::unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);

  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  return std::move(query);
}
