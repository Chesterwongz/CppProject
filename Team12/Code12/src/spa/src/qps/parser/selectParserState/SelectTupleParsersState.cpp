#include "SelectTupleParsersState.h"

#include <utility>

PredictiveMap SelectTupleParsersState::predictiveMap = {
    {PQL_LEFT_ANGLE_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_RIGHT_ANGLE_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_SYNONYM_TOKEN}}};

SelectTupleParsersState::SelectTupleParsersState(
    PQLParserContext& parserContext, PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void SelectTupleParsersState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN: {
        unique_ptr<SynonymArg> syn = std::make_unique<SynonymArg>(
            token.getValue(),
            parserContext.getValidSynonymType(token.getValue()));
        processAttrRef(syn);
        synonymsToSelect.push_back(std::move(syn));
        break;
      }
      case PQL_RIGHT_ANGLE_TOKEN:
        parserContext.addSelectClause(std::move(synonymsToSelect));
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT);
}
