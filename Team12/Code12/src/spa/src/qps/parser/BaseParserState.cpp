#include "BaseParserState.h"

unordered_set<PQLTokenType> BaseParserState::startTokensOfAvailClauses = {
    PQL_SUCH_TOKEN, PQL_PATTERN_TOKEN};

BaseParserState::BaseParserState(PQLParserContext &parserContext,
                                 PQLTokenType prev)
    : parserContext(parserContext), prev(prev) {}
