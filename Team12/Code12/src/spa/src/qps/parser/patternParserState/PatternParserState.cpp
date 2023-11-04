#include "PatternParserState.h"

#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

PredictiveMap PatternParserState::predictiveMap = {
    {PQL_PATTERN_TOKEN, {PQL_SYNONYM_TOKEN, PQL_NOT_TOKEN}},
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
  if (next.has_value() && next->getType() == PQL_OPEN_BRACKET_TOKEN ||
      isInBracket) {
    BaseParserState::processNameToken(curr);
    if (syn &&
        parserContext.getValidSynonymType(curr.getValue()) != VARIABLE_ENTITY) {
      parserContext.setSemanticallyInvalid();
    }
  } else {
    PQLTokenType toUpdate =
        PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(toUpdate);
  }
}

void PatternParserState::checkSafeExit() {
  if (!syn || !firstArg) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
  bool isValidIfPattern = nonFirstArgs.size() == IF_ARG_COUNT &&
                          nonFirstArgs[0]->isWildcard() &&
                          nonFirstArgs[1]->isWildcard();
  if (isValidIfPattern) {
    parsedPatternState = IF_PATTERN;
    return;
  }
  bool isValidAssignWhilePattern =
      nonFirstArgs.size() == ASSIGN_WHILE_ARG_COUNT &&
      (nonFirstArgs[0]->isWildcard() || nonFirstArgs[0]->isPatternExp());
  if (isValidAssignWhilePattern) {
    parsedPatternState = ASSIGN_WHILE_PATTERN;
    return;
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
}

void PatternParserState::createPatternClause() {
  string synEntity = syn->getEntityType();
  if (parsedPatternState == ASSIGN_WHILE_PATTERN) {
    if (synEntity == ASSIGN_ENTITY) {
      unique_ptr<AssignPatternClause> assignPatternClause =
          std::make_unique<AssignPatternClause>(
              std::move(syn), std::move(firstArg), std::move(nonFirstArgs[0]),
              isPartialMatch);

      if (isNegated) {
        parserContext.addClause(
            std::make_unique<NotDecorator>(std::move(assignPatternClause)));
        return;
      }
      parserContext.addClause(std::move(assignPatternClause));
      return;
    }
    if (synEntity == WHILE_ENTITY && nonFirstArgs[0]->isWildcard()) {
      unique_ptr<WhilePatternClause> whilePatternClause =
          std::make_unique<WhilePatternClause>(std::move(syn),
                                               std::move(firstArg));
      if (isNegated) {
        parserContext.addClause(
            std::make_unique<NotDecorator>(std::move(whilePatternClause)));
        return;
      }
      parserContext.addClause(std::move(whilePatternClause));
      return;
    }
  } else if (parsedPatternState == IF_PATTERN && synEntity == IF_ENTITY) {
    unique_ptr<IfPatternClause> ifPatternClause =
        std::make_unique<IfPatternClause>(std::move(syn), std::move(firstArg));

    if (isNegated) {
      parserContext.addClause(
          std::make_unique<NotDecorator>(std::move(ifPatternClause)));
      return;
    }
    parserContext.addClause(std::move(ifPatternClause));
    return;
  }
  parserContext.setSemanticallyInvalid();
}

void PatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);
  NonFirstArgPatternParserState subPatternState(parserContext, PQL_COMMA_TOKEN);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_NOT_TOKEN:
        isNegated = true;
        break;
      case PQL_OPEN_BRACKET_TOKEN:
        isInBracket = true;
        break;
      case PQL_SYNONYM_TOKEN: {
        unique_ptr<SynonymArg> currSyn = std::make_unique<SynonymArg>(
            token.getValue(),
            parserContext.getValidSynonymType(token.getValue()));
        if (!syn) {
          syn = std::move(currSyn);
        } else {
          firstArg = std::move(currSyn);
        }
        break;
      }
      case PQL_LITERAL_REF_TOKEN:
        firstArg = std::make_unique<Ident>(token.getValue());
        break;
      case PQL_WILDCARD_TOKEN:
        firstArg = std::make_unique<Wildcard>();
        break;
      case PQL_COMMA_TOKEN:
        subPatternState.handleToken();
        nonFirstArgs = subPatternState.getNonFirstArgs();
        isPartialMatch = subPatternState.getIsPartialMatch();
        checkSafeExit();
        createPatternClause();
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
