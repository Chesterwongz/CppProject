#include "PatternParserState.h"

#include "qps/parser/patternParserState/assignPatternParserState/AssignPatternParserState.h"

PredictiveMap PatternParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_PATTERN_TOKEN}},
    {PQL_PATTERN_TOKEN, {PQL_ASSIGN_PATTERN_TOKEN}}};

PatternParserState::PatternParserState(PQLParserContext& parserContext,
                                       PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

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
  } else {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_INVALID_PATTERN_SYN);
  }
}

void PatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (!curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_ASSIGN_PATTERN_TOKEN:
        parserContext.transitionTo(std::make_unique<AssignPatternParserState>(
            parserContext, token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
}
