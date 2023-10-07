#include "PatternParserState.h"

#include "qps/parser/patternParserState/assignPatternParserState/AssignPatternParserState.h"

PredictiveMap PatternParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_PATTERN_TOKEN}},
    {PQL_PATTERN_TOKEN, {PQL_ASSIGN_PATTERN_TOKEN}}};

PatternParserState::PatternParserState(PQLParserContext& parserContext)
    : BaseParserState(parserContext) {}

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
  while (!this->tokenStream.isTokenStreamEnd()) {
    auto& curr = tokenStream.getCurrentToken();

    if (curr.getType() == PQL_NAME_TOKEN) {
      processNameToken(curr);
    }

    if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
      throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
    }

    switch (curr.getType()) {
      case PQL_PATTERN_TOKEN:
        break;
      case PQL_ASSIGN_PATTERN_TOKEN:
        parserContext.transitionTo(
            std::make_unique<AssignPatternParserState>(parserContext));
        return;
      default:
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
    }
    this->prev = curr.getType();
    tokenStream.next();
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
}
