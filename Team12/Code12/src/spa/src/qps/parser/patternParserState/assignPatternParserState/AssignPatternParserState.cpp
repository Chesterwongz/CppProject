#include "AssignPatternParserState.h"

#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"
#include "qps/parser/suchThatParserState/SuchThatParserState.h"

PredictiveMap AssignPatternParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_ASSIGN_PATTERN_TOKEN}},
    {PQL_ASSIGN_PATTERN_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_WILDCARD_TOKEN,
     {PQL_COMMA_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_LITERAL_EXPRESSION_TOKEN,
      PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN,
     {PQL_COMMA_TOKEN, PQL_WILDCARD_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_EXPRESSION_TOKEN,
     {PQL_WILDCARD_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_LITERAL_EXPRESSION_TOKEN}},
    {PQL_CLOSE_BRACKET_TOKEN, startTokensOfAvailClauses}};

PQLTokenType AssignPatternParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

AssignPatternParserState::AssignPatternParserState(
    PQLParserContext& parserContext)
    : BaseParserState(parserContext),
      isInBracket(false),
      isPartialMatch(false),
      secondArgWildcardCount(0) {}

void AssignPatternParserState::processNameToken(PQLToken& curr) {
  if (prev == PQL_OPEN_BRACKET_TOKEN) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
  } else {
    curr.updateTokenType(
        PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
  }
}

void AssignPatternParserState::processSynonymToken(PQLToken& curr) {
  string synType = parserContext.getValidSynonymType(curr.getValue());

  if (patternArg.size() != FIRST_ARG) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }

  if (synType == VARIABLE_ENTITY) {
    patternArg.push_back(
        std::move(std::make_unique<SynonymArg>(curr.getValue())));
  } else {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_VAR_SYN);
  }
}

void AssignPatternParserState::processLastArgument() {
  bool isWildcardMatch = patternArg.size() == SECOND_ARG &&
                         secondArgWildcardCount == WILDCARD_MATCH_COUNT;
  bool isExactMatch = patternArg.size() == maxNumberOfArgs &&
                      secondArgWildcardCount == EXACT_MATCH_COUNT;
  isPartialMatch = secondArgWildcardCount == PARTIAL_MATCH_COUNT &&
                   patternArg.size() == maxNumberOfArgs;

  if (isWildcardMatch) {
    patternArg.push_back(std::move(std::make_unique<Wildcard>()));
  } else if (isPartialMatch || isExactMatch) {
    return;
  } else {
    throw QPSSyntaxError(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
  }
}

void AssignPatternParserState::checkIsValidIdent(const std::string& ref) {
  if (patternArg.size() == FIRST_ARG && !QPSStringUtils::isIdentValue(ref)) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_IDENT);
  }
}

void AssignPatternParserState::checkIsValidExpr(const std::string& ref) {
  if (!ExpressionValidator::isValidExpression(ref)) {
    throw QPSSyntaxError(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
  }
}

void AssignPatternParserState::handleToken() {
  while (!this->tokenStream.isTokenStreamEnd()) {
    auto& curr = tokenStream.getCurrentToken();

    if (curr.getType() == PQL_NAME_TOKEN) {
      processNameToken(curr);
    }

    if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
      throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
    }

    switch (curr.getType()) {
      case PQL_ASSIGN_PATTERN_TOKEN:
        synAssign = std::make_unique<SynonymArg>(curr.getValue());
      case PQL_COMMA_TOKEN:
        break;
      case PQL_SYNONYM_TOKEN:
        processSynonymToken(curr);
        break;
      case PQL_OPEN_BRACKET_TOKEN:
        isInBracket = true;
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        isInBracket = false;
        processLastArgument();
        parserContext.addClause(std::make_unique<PatternClause>(
            std::move(synAssign), std::move(patternArg), isPartialMatch));
        break;
      case PQL_WILDCARD_TOKEN:
        if (patternArg.size() >= SECOND_ARG) {
          secondArgWildcardCount++;
        } else {
          patternArg.push_back(std::move(std::make_unique<Wildcard>()));
        }
        break;
      case PQL_LITERAL_REF_TOKEN:
        checkIsValidIdent(curr.getValue());
        patternArg.push_back(
            std::move(std::make_unique<Ident>(curr.getValue())));
        break;
      case PQL_LITERAL_EXPRESSION_TOKEN:
        checkIsValidExpr(curr.getValue());
        patternArg.push_back(
            std::move(std::make_unique<Ident>(curr.getValue())));
        break;
      case PQL_SUCH_TOKEN:
        this->parserContext.transitionTo(
            std::make_unique<SuchThatParserState>(parserContext));
        return;
      default:
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
    }
    this->prev = curr.getType();
    tokenStream.next();
  }
  if (prev != exitToken || isInBracket) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
}
