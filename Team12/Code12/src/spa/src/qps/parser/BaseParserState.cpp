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

string BaseParserState::getValidAttrRef(const std::string &synonym,
                                        const std::string &attrRef) {
  auto entityType = parserContext.getValidSynonymType(synonym);

  if (PQLParserUtils::isValidAttrRefFromSynonym(entityType, attrRef)) {
    return attrRef;
  }
  parserContext.setSemanticallyInvalid();
  return ATTR_REF_INVALID;
}

void BaseParserState::processAttrRef(unique_ptr<SynonymArg> &synArg) {
  // must be a syn to enter here; peek will be peeking the next token after syn
  auto next = parserContext.peekNextToken();
  if (prevClauseType == ClauseType::WITH_CLAUSE &&
      (!next.has_value() || next->getType() == PQL_PERIOD_TOKEN)) {
    throw QPSSyntaxError(QPS_SYNTAX_ERR_INVALID_WITH);
  }
  if (!next.has_value()) return;

  if (next->getType() != PQL_PERIOD_TOKEN) return;

  parserContext.eatCurrToken();  // eat period
  auto attrRef = parserContext.eatCurrToken();
  if (!attrRef.has_value()) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR);
  }
  auto validRef = getValidAttrRef(synArg->getValue(), attrRef->getValue());
  synArg->setAttrRef(std::move(validRef));
}
