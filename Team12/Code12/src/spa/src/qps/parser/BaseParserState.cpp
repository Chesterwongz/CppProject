#include "BaseParserState.h"

BaseParserState::BaseParserState(PQLParserContext &parserContext,
                                 PQLTokenType prev)
    : parserContext(parserContext), prev(prev) {}

void BaseParserState::processNameToken(PQLToken &curr) {
  curr.updateTokenType(PQL_SYNONYM_TOKEN);
}
