#include "ClauseTransitionParserState.h"

ClauseTransitionParserState::ClauseTransitionParserState(
    PQLParserContext &parserContext)
    : parserContext(parserContext) {}

void ClauseTransitionParserState::processNameToken(PQLToken &curr) {
  // has to be a keyword
  PQLTokenType toUpdate =
      PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
  curr.updateTokenType(toUpdate);
}

void ClauseTransitionParserState::setClauseTransitionState(
    PQLParserContext &pc) {
  pc.transitionTo(std::make_unique<ClauseTransitionParserState>(pc));
}

void ClauseTransitionParserState::handleToken() {
  auto curr = parserContext.eatCurrToken();

  if (!curr.has_value()) return;

  processNameToken(curr.value());

  switch (curr->getType()) {
    case PQL_SUCH_TOKEN:
      this->parserContext.transitionTo(std::make_unique<SuchThatParserState>(
          parserContext, curr->getType()));
      return;
    case PQL_PATTERN_TOKEN:
      this->parserContext.transitionTo(
          std::make_unique<PatternParserState>(parserContext, curr->getType()));
      return;
    default:
      throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr->getValue());
  }
}
