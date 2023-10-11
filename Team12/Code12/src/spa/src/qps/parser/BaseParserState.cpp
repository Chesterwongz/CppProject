#include "BaseParserState.h"

BaseParserState::BaseParserState(PQLParserContext &parserContext,
                                 PQLTokenType prev)
    : parserContext(parserContext), prev(prev) {}
