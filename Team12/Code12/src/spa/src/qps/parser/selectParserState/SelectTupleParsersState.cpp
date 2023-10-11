#include "SelectTupleParsersState.h"

PredictiveMap SelectTupleParsersState::predictiveMap = {
    {PQL_LEFT_ANGLE_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_RIGHT_ANGLE_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_SYNONYM_TOKEN}}
};

SelectTupleParsersState::SelectTupleParsersState(
    PQLParserContext& parserContext, PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void SelectTupleParsersState::processNameToken(PQLToken& curr) {
  curr.updateTokenType(PQL_SYNONYM_TOKEN);
}

void SelectTupleParsersState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN:
        parserContext.getValidSynonymType(token.getValue());
        synonymsToSelect.push_back(
            std::make_unique<SynonymArg>(token.getValue()));
        break;
      case PQL_RIGHT_ANGLE_TOKEN:
        // TODO(Hwee):
        //  parserContext.addSelectClause(std::move(synonymsToSelect));
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
}
