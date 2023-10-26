#include "PQLParserTestUtils.h"

PKBStore dummyQpsParserStore{};
PKBReader dummyQpsParserPkbReader(dummyQpsParserStore);

std::unique_ptr<Query> parseToQuery(const std::vector<PQLToken>& tokenList) {
  std::unique_ptr<PQLTokenStream> tokenStreamPtr =
      std::make_unique<PQLTokenStream>(tokenList);

  std::unique_ptr<Query> query = std::make_unique<Query>();

  PQLParserContext parserContext(std::move(tokenStreamPtr), query);
  std::unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);

  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  return std::move(query);
}

std::unique_ptr<Query> parseStringToQuery(const string& query) {
  unique_ptr<Query> queryObj = std::make_unique<Query>();
  unique_ptr<PQLTokenStream> tokenStream = PQLTokenizer::tokenize(query);

  PQLParserContext parserContext(std::move(tokenStream), queryObj);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));

  parserContext.handleTokens();

  return std::move(queryObj);
}
