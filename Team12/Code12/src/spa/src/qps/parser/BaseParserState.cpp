#include "BaseParserState.h"

BaseParserState::BaseParserState(PQLParserContext &parserContext,
                                 PQLTokenType prev)
    : parserContext(parserContext), prev(prev) {}

void BaseParserState::processNameToken(PQLToken &curr) {
  if (!QPSStringUtils::isSynonym(curr.getValue())) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_SYNONYM + curr.getValue());
  }
  curr.updateTokenType(PQL_SYNONYM_TOKEN);
}
