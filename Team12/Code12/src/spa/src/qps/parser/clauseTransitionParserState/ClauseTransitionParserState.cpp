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

void ClauseTransitionParserState::createAndClause(PQLParserContext &pc) {
  switch (prevClauseType) {
    case SUCH_THAT_CLAUSE:
      this->parserContext.transitionTo(
          std::make_unique<SuchThatParserState>(pc, PQL_THAT_TOKEN));
      return;
    case PATTERN_CLAUSE:
      this->parserContext.transitionTo(std::make_unique<PatternParserState>(
          parserContext, PQL_PATTERN_TOKEN));
      return;
    default:
      throw QPSSyntaxError(QPS_SYNTAX_ERR_AND);
  }
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
    case PQL_AND_TOKEN:
      createAndClause(parserContext);
      return;
    default:
      throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr->getValue());
  }
}
