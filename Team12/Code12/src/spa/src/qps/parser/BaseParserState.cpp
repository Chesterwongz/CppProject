#include "BaseParserState.h"

BaseParserState::BaseParserState(PQLParserContext &parserContext) :
    parserContext(parserContext),
    tokenStream(this->parserContext.getTokenStream()),
    prev(PQL_NULL_TOKEN) {}
