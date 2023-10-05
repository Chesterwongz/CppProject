#include "ModifiesParserState.h"

#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/patternParserState/PatternParserState.h"

PredictiveMap ModifiesParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_MODIFIES_TOKEN}},
    {PQL_MODIFIES_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_INTEGER_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_INTEGER_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_CLOSE_BRACKET_TOKEN, {PQL_PATTERN_TOKEN}}};

PQLTokenType ModifiesParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

size_t ModifiesParserState::maxNumberOfArgs = 2;

ModifiesParserState::ModifiesParserState(PQLParserContext& parserContext)
    : parserContext(parserContext),
      tokenStream(this->parserContext.getTokenStream()),
      prev(PQL_NULL_TOKEN),
      RelationshipParserState(false) {}

void ModifiesParserState::handleToken() {
  while (!this->tokenStream.isTokenStreamEnd()) {
    auto& curr = tokenStream.getCurrentToken();

    if (curr.getType() == PQL_NAME_TOKEN) {
      processNameToken(curr);
    }

    if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
      throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
    }

    switch (curr.getType()) {
      case PQL_MODIFIES_TOKEN:
      case PQL_COMMA_TOKEN:
        break;
      case PQL_OPEN_BRACKET_TOKEN:
        isInBracket = true;
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        isInBracket = false;
        checkSafeExit(maxNumberOfArgs, arguments.size());
        parserContext.addClause(make_unique<SuchThatClause>(
            MODIFIES_ENUM, std::move(arguments.at(0)),
            std::move(arguments.at(1)), false));
        break;
      case PQL_SYNONYM_TOKEN:
        parserContext.checkValidSynonym(curr.getValue());
        checkValidSecondArg(curr);
        arguments.push_back(
            std::move(std::make_unique<SynonymArg>(curr.getValue())));
        break;
      case PQL_WILDCARD_TOKEN:
        arguments.push_back(std::move(std::make_unique<Wildcard>()));
        break;
      case PQL_LITERAL_REF_TOKEN:
        arguments.push_back(
            std::move(std::make_unique<Ident>(curr.getValue())));
        break;
      case PQL_INTEGER_TOKEN:
        arguments.push_back(
            std::move(std::make_unique<Integer>(curr.getValue())));
        break;
      case PQL_PATTERN_TOKEN:
        this->parserContext.transitionTo(
            make_unique<PatternParserState>(parserContext));
        return;
      default:
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
    }
    this->prev = curr.getType();
    tokenStream.next();
  }
  // safety barrier for premature exit
  checkSafeExit(maxNumberOfArgs, arguments.size());
}

void ModifiesParserState::checkValidSecondArg(PQLToken(&curr)) {
  if (arguments.size() == 0) return;

  auto entity = parserContext.getSynonymType(curr.getValue());
  if (entity != VARIABLE_ENTITY) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_INCORRECT_ARGUMENT);
  }
}
