#include "SelectTupleParsersState.h"

PredictiveMap SelectTupleParsersState::predictiveMap = {
    {PQL_LEFT_ANGLE_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_RIGHT_ANGLE_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_RIGHT_ANGLE_TOKEN, startTokensOfAvailClauses}
};

PQLTokenType SelectTupleParsersState::exitToken = PQL_RIGHT_ANGLE_TOKEN;

SelectTupleParsersState::SelectTupleParsersState(
    PQLParserContext& parserContext,
    PQLTokenType prev)
    : isInBracket(true), BaseParserState(parserContext, prev) {}

void SelectTupleParsersState::processNameToken(PQLToken& curr) {
  if (isInBracket) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
  } else {
    PQLTokenType toUpdate =
        PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(toUpdate);
  }
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
        isInBracket = false;
//      TODO(Hwee): parserContext.addSelectClause(std::move(synonymsToSelect));
        break;
      case PQL_SUCH_TOKEN:
        parserContext.transitionTo(std::make_unique<SuchThatParserState>(
            parserContext, token.getType()));
        return;
      case PQL_PATTERN_TOKEN:
        parserContext.transitionTo(std::make_unique<PatternParserState>(
            parserContext, token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  if (isInBracket || prev != exitToken) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT);
  }
}
