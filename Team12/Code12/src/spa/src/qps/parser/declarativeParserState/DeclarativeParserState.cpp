#include "DeclarativeParserState.h"

#include "qps/parser/selectParserState/SelectParserState.h"

PredictiveMap DeclarativeParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN}},
    {PQL_ENTITY_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_SEMICOLON_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SEMICOLON_TOKEN, {PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN}}};

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext)
    : BaseParserState(parserContext, PQL_NULL_TOKEN) {
  prevClauseType = ClauseType::NULL_CLAUSE;
}

void DeclarativeParserState::processNameToken(PQLToken& curr) {
  bool expectedSyn = (prev == PQL_ENTITY_TOKEN || prev == PQL_COMMA_TOKEN);

  if (expectedSyn) {
    if (!QPSStringUtils::isSynonym(curr.getValue())) {
      throw QPSSyntaxError(QPS_TOKENIZATION_ERR_SYNONYM);
    }
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
