#include "ClauseTransitionParserState.h"

ClauseTransitionParserState::ClauseTransitionParserState(
    PQLParserContext& parserContext)
    : parserContext(parserContext) {}

bool ClauseTransitionParserState::isTerminable() {
  return true;
}

void ClauseTransitionParserState::processNameToken(PQLToken& curr) {
  // has to be a keyword
  PQLTokenType toUpdate =
      PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
  curr.updateTokenType(toUpdate);
}

void ClauseTransitionParserState::setClauseTransitionState(
    PQLParserContext& pc) {
  pc.transitionTo(std::make_unique<ClauseTransitionParserState>(pc));
}

void ClauseTransitionParserState::createAndClause() {
  switch (prevClauseType) {
    case ClauseType::SUCH_THAT_CLAUSE:
      this->parserContext.transitionTo(
          std::make_unique<SuchThatParserState>(parserContext, PQL_THAT_TOKEN));
      return;
    case ClauseType::PATTERN_CLAUSE:
      this->parserContext.transitionTo(std::make_unique<PatternParserState>(
          parserContext, PQL_PATTERN_TOKEN));
      return;
    case ClauseType::WITH_CLAUSE:
      this->parserContext.transitionTo(
          std::make_unique<WithParserState>(parserContext, PQL_WITH_TOKEN));
      return;
    default:
      throw QPSSyntaxError(QPS_SYNTAX_ERR_AND);
  }
}

void ClauseTransitionParserState::handleToken() {
  auto curr = parserContext.eatCurrToken();

  if (!curr.has_value()) return;

  if (!parserContext.peekNextToken().has_value()) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
  }

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
    case PQL_WITH_TOKEN:
      this->parserContext.transitionTo(
          std::make_unique<WithParserState>(parserContext, PQL_WITH_TOKEN));
      return;
    case PQL_AND_TOKEN:
      createAndClause();
      return;
    default:
      throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr->getValue());
  }
}
