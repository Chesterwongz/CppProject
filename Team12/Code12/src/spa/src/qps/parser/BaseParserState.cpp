#include "BaseParserState.h"

unordered_set<PQLTokenType> BaseParserState::startTokensOfAvailClauses = {
    PQL_SUCH_TOKEN, PQL_PATTERN_TOKEN};

unordered_set<PQLTokenType>
    BaseParserState::startTokensOfAvailClausesForSelect = {
        PQL_SUCH_TOKEN, PQL_PATTERN_TOKEN, PQL_LEFT_ANGLE_TOKEN};

BaseParserState::BaseParserState(PQLParserContext &parserContext,
                                 PQLTokenType prev)
    : parserContext(parserContext), prev(prev) {}
