#include "SelectParserState.h"

PredictiveMap SelectParserState::predictiveMap = {
    {PQL_SELECT_TOKEN, {PQL_SYNONYM_TOKEN, PQL_LEFT_ANGLE_TOKEN}},
    {PQL_SYNONYM_TOKEN, startTokensOfAvailClausesForSelect}};

PQLTokenType SelectParserState::exitToken = PQL_SYNONYM_TOKEN;

SelectParserState::SelectParserState(PQLParserContext& parserContext,
                                     PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void SelectParserState::processNameToken(PQLToken& curr) {
  if (prev == PQL_SELECT_TOKEN) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
  } else {
    PQLTokenType toUpdate =
        PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(toUpdate);
  }
}

void SelectParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN:
        // TODO(Hwee): change to add vector syn
        parserContext.addSelectClause(token.getValue());
        break;
      case PQL_SUCH_TOKEN:
        parserContext.transitionTo(std::make_unique<SuchThatParserState>(
            parserContext, token.getType()));
        return;
      case PQL_PATTERN_TOKEN:
        parserContext.transitionTo(std::make_unique<PatternParserState>(
            parserContext, token.getType()));
        return;
      case PQL_LEFT_ANGLE_TOKEN:
        parserContext.transitionTo(std::make_unique<SelectTupleParsersState>(
            parserContext, token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  if (prev != exitToken) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT);
  }
}
