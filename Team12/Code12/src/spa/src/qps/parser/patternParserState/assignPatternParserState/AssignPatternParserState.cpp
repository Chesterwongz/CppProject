#include "AssignPatternParserState.h"

#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/patternParserState/PatternParserState.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"
#include "qps/parser/suchThatParserState/SuchThatParserState.h"

PredictiveMap AssignPatternParserState::predictiveMap = {
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
    PQLParserContext& parserContext, PQLTokenType prev,
    unique_ptr<SynonymArg> synAssign)
    : BaseParserState(parserContext, prev),
      isPartialMatch(false),
      synAssign(std::move(synAssign)),
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

// TODO(Hwee): Review and remove redundant logic
void AssignPatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN:
        processSynonymToken(token);
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        processLastArgument();
        parserContext.addClause(std::make_unique<PatternClause>(
            std::move(synAssign), std::move(patternArg), isPartialMatch));
        break;
      case PQL_WILDCARD_TOKEN:
        if (patternArg.size() >= SECOND_ARG) {
          secondArgWildcardCount++;
        } else {
          patternArg.push_back(std::make_unique<Wildcard>());
        }
        break;
      case PQL_LITERAL_REF_TOKEN:
        checkIsValidIdent(token.getValue());
        patternArg.push_back(
            std::move(std::make_unique<Ident>(token.getValue())));
        break;
      case PQL_LITERAL_EXPRESSION_TOKEN:
        checkIsValidExpr(token.getValue());
        patternArg.push_back(
            std::move(std::make_unique<Ident>(token.getValue())));
        break;
      case PQL_SUCH_TOKEN:
        this->parserContext.transitionTo(std::make_unique<SuchThatParserState>(
            parserContext, token.getType()));
        return;
      case PQL_PATTERN_TOKEN:
        this->parserContext.transitionTo(std::make_unique<PatternParserState>(
            parserContext, token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  if (prev != exitToken) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
}
