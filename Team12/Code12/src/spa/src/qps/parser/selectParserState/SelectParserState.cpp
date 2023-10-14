#include "SelectParserState.h"

PredictiveMap SelectParserState::predictiveMap = {
    {PQL_SELECT_TOKEN, {PQL_SYNONYM_TOKEN, PQL_LEFT_ANGLE_TOKEN}}};

SelectParserState::SelectParserState(PQLParserContext& parserContext,
                                     PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void SelectParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN:
        // TODO(Hwee): change to add vector syn
        parserContext.addSelectClause(token.getValue());
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
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
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT);
}
