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

string BaseParserState::checkValidAttrRef(const std::string& synonym,
                                        std::string attrRef) {
  auto entityType = parserContext.getValidSynonymType(synonym);

  if (PQLParserUtils::isValidAttrRefFromSynonym(synonym, attrRef)) {
    return attrRef;
  }
  throw QPSSemanticError(QPS_SEMANTIC_ERR_INVALID_ATTR_REF);
}

void BaseParserState::processAttrRef(unique_ptr<SynonymArg> &synArg) {
  // must be a syn to enter here; peek will be peeking the next token after syn
  auto next = parserContext.peekNextToken();
  if (!next.has_value()) return;

  if (next->getType() != PQL_PERIOD_TOKEN) return;

  parserContext.eatCurrToken();  // eat period
  auto attrRef = parserContext.eatCurrToken();
  if (!attrRef.has_value()) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR + attrRef->getValue());
  }
  auto validRef = checkValidAttrRef(synArg->getValue(), attrRef->getValue());
  synArg->setAttrRef(validRef);
}
