#include "PatternParserState.h"

PredictiveMap PatternParserState::predictiveMap = {
    {PQL_PATTERN_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_NOT_TOKEN, {PQL_SYNONYM_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_WILDCARD_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_OPEN_BRACKET_TOKEN, PQL_COMMA_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN}},
};
PatternParserState::PatternParserState(PQLParserContext& parserContext,
                                       PQLTokenType prev)
    : BaseParserState(parserContext, prev) {
  prevClauseType = ClauseType::PATTERN_CLAUSE;
}

void PatternParserState::processNameToken(PQLToken& curr) {
  auto next = parserContext.peekNextToken();
  if (next.has_value() && next->getType() == PQL_OPEN_BRACKET_TOKEN) {
    BaseParserState::processNameToken(curr);
  } else {
    PQLTokenType toUpdate =
        PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(toUpdate);
  }
}

void PatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_NOT_TOKEN:
        isNegated = true;
        break;
      case PQL_SYNONYM_TOKEN:
        // semantically invalid but must ensure that it has no syntactic err
        parserContext.snapTokenStreamImage();
        // chain of responsibilities start here
        parserContext.transitionTo(std::make_unique<AssignPatternParserState>(
            parserContext, token.getType(),
            std::make_unique<SynonymArg>(
                token.getValue(),
                parserContext.getValidSynonymType(token.getValue())),
            isNegated));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
