#include "NonFirstArgPatternParserState.h"

PredictiveMap NonFirstArgPatternParserState::predictiveMap = {
    {PQL_COMMA_TOKEN,
     {PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_LITERAL_EXPRESSION_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_EXPRESSION_TOKEN, {PQL_CLOSE_BRACKET_TOKEN}},
};

NonFirstArgPatternParserState::NonFirstArgPatternParserState(
    PQLParserContext& parserContext, PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void NonFirstArgPatternParserState::processWildcard() {
  auto nextToken = parserContext.peekNextToken();
  if (!nextToken.has_value()) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
  auto nextType = nextToken->getType();

  if (nextType == PQL_COMMA_TOKEN) {
    secondPatternArg.emplace_back(std::make_unique<Wildcard>());
    return;
  }

  // _LITERAL_
  if (nextType == PQL_LITERAL_REF_TOKEN ||
      nextType == PQL_LITERAL_EXPRESSION_TOKEN) {
    auto patternExp = parserContext.eatCurrToken();  // eat patternExp token
    checkIsValidExpr(patternExp->getValue());
    secondPatternArg.emplace_back(
        std::make_unique<PatternExp>(patternExp->getValue()));
  }

  auto wildcardToken = parserContext.eatCurrToken();
  if (!wildcardToken.has_value() ||
      wildcardToken->getType() != PQL_WILDCARD_TOKEN) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
  isPartialMatch = true;
}

void NonFirstArgPatternParserState::checkIsValidExpr(const std::string& ref) {
  if (!ExpressionValidator::isValidExpression(ref)) {
    throw QPSSyntaxError(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
  }
}

vector<unique_ptr<AbstractArgument>>
NonFirstArgPatternParserState::getNonFirstArgs() {
  return std::move(secondPatternArg);
}

bool NonFirstArgPatternParserState::getIsPartialMatch() const {
  return isPartialMatch;
}

void NonFirstArgPatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_CLOSE_BRACKET_TOKEN:
        return;
      case PQL_WILDCARD_TOKEN:
        processWildcard();
        break;
      case PQL_LITERAL_REF_TOKEN:
      case PQL_LITERAL_EXPRESSION_TOKEN:
        checkIsValidExpr(token.getValue());
        secondPatternArg.emplace_back(
            std::make_unique<PatternExp>(token.getValue()));
        break;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
