#include "PatternParserState.h"

PredictiveMap PatternParserState::predictiveMap = {
    {PQL_PATTERN_TOKEN,
     {PQL_NOT_TOKEN, PQL_ASSIGN_PATTERN_TOKEN, PQL_IF_PATTERN_TOKEN,
      PQL_WHILE_PATTERN_TOKEN}},
    {PQL_NOT_TOKEN,
     {PQL_ASSIGN_PATTERN_TOKEN, PQL_IF_PATTERN_TOKEN,
      PQL_WHILE_PATTERN_TOKEN}}};

PatternParserState::PatternParserState(PQLParserContext& parserContext,
                                       PQLTokenType prev)
    : BaseParserState(parserContext, prev) {
  prevClauseType = PATTERN_CLAUSE;
}

void PatternParserState::processNameToken(PQLToken& curr) {
  if (prev == PQL_NULL_TOKEN) {
    PQLTokenType toUpdate =
        PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(toUpdate);
  } else {
    processSynonymToken(curr);
  }
}

void PatternParserState::processSynonymToken(PQLToken& curr) {
  string synType = parserContext.getValidSynonymType(curr.getValue());

  if (synType == ASSIGN_ENTITY) {
    curr.updateTokenType(PQL_ASSIGN_PATTERN_TOKEN);
  } else if (synType == IF_ENTITY) {
    curr.updateTokenType(PQL_IF_PATTERN_TOKEN);
  } else if (synType == WHILE_ENTITY) {
    curr.updateTokenType(PQL_WHILE_PATTERN_TOKEN);
  } else {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_INVALID_PATTERN_SYN);
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
      case PQL_ASSIGN_PATTERN_TOKEN:
        parserContext.transitionTo(std::make_unique<AssignPatternParserState>(
            parserContext, token.getType(),
            std::make_unique<SynonymArg>(token.getValue(), ASSIGN_ENTITY),
            isNegated));
        return;
      case PQL_IF_PATTERN_TOKEN:
        parserContext.transitionTo(std::make_unique<IfPatternParserState>(
            parserContext, token.getType(),
            std::make_unique<SynonymArg>(token.getValue(), IF_ENTITY),
            isNegated));
        return;
      case PQL_WHILE_PATTERN_TOKEN:
        parserContext.transitionTo(std::make_unique<WhilePatternParserState>(
            parserContext, token.getType(),
            std::make_unique<SynonymArg>(token.getValue(), WHILE_ENTITY),
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
