#include "SelectParserState.h"

PredictiveMap SelectParserState::predictiveMap = {
    {PQL_SELECT_TOKEN,
     {PQL_BOOLEAN_TOKEN, PQL_SYNONYM_TOKEN, PQL_LEFT_ANGLE_TOKEN}}};

SelectParserState::SelectParserState(PQLParserContext& parserContext,
                                     PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void SelectParserState::processNameToken(PQLToken& curr) {
  if (parserContext.checkSynonymExists(curr.getValue())) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
  } else if (curr.getValue() == BOOLEAN_KEYWORD) {
    curr.updateTokenType(PQL_BOOLEAN_TOKEN);
  } else {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_UNDECLARED_SYNONYM +
                           curr.getValue());
  }
}

void SelectParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_BOOLEAN_TOKEN:
        parserContext.addSelectClause();
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      case PQL_SYNONYM_TOKEN: {
        unique_ptr<SynonymArg> selectedSyn = std::make_unique<SynonymArg>(
            token.getValue(),
            parserContext.getValidSynonymType(token.getValue()));
        processAttrRef(selectedSyn);
        parserContext.addSelectClause(std::move(selectedSyn));
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      }
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
