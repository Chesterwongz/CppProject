#include "BaseParserState.h"

unordered_set<PQLTokenType> BaseParserState::startTokensOfAvailClauses = {
    PQL_SUCH_TOKEN, PQL_PATTERN_TOKEN};

BaseParserState::BaseParserState(PQLParserContext &parserContext)
    : parserContext(parserContext),
      tokenStream(this->parserContext.getTokenStream()),
      prev(PQL_NULL_TOKEN) {}
