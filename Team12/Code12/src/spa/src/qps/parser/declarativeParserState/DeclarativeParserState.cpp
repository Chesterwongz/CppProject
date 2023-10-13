#include "DeclarativeParserState.h"

#include "qps/parser/selectParserState/SelectParserState.h"

PredictiveMap DeclarativeParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN}},
    {PQL_ENTITY_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_SEMICOLON_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SEMICOLON_TOKEN, {PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN}}};

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext)
    : BaseParserState(parserContext, PQL_NULL_TOKEN) {}

void DeclarativeParserState::processNameToken(PQLToken& curr) {
  if (prev == PQL_ENTITY_TOKEN || prev == PQL_COMMA_TOKEN) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
  } else {
    auto tokenType = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(tokenType);
  }
}

void DeclarativeParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_ENTITY_TOKEN:
        this->currentEntity = token.getValue();
        break;
      case PQL_SYNONYM_TOKEN:
        this->parserContext.addToContext(this->currentEntity, token.getValue());
        break;
      case PQL_SELECT_TOKEN:
        this->parserContext.transitionTo(std::make_unique<SelectParserState>(
            parserContext, token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }

  // should never exit in this parser
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_DECLARATION);
}
