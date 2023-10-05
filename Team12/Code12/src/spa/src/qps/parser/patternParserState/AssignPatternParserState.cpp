#include "AssignPatternParserState.h"

#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/suchThatParserState/SuchThatParserState.h"

PredictiveMap AssignPatternParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_ASSIGN_PATTERN_TOKEN}},
    {PQL_ASSIGN_PATTERN_TOKEN, {PQL_OPEN_BRACKET_TOKEN, PQL_COMMA_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_WILDCARD_TOKEN,
     {PQL_COMMA_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN,
     {PQL_COMMA_TOKEN, PQL_WILDCARD_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_CLOSE_BRACKET_TOKEN, {PQL_SUCH_TOKEN}}};

PQLTokenType AssignPatternParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

size_t AssignPatternParserState::maxNumberOfArgs = 2;

AssignPatternParserState::AssignPatternParserState(PQLParserContext& parserContext)
    : BaseParserState(parserContext),
      isInBracket(false),
      argumentCount(0),
      partialMatchWildCardCount(0) {}

void AssignPatternParserState::processNameToken(PQLToken& curr) {
  if (prev == PQL_OPEN_BRACKET_TOKEN) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
  }
}

// feels like should change it up after ms2, not OOP
void AssignPatternParserState::processSynonymToken(PQLToken& curr) {
  string synType = parserContext.checkValidSynonym(curr.getValue());

  if (argumentCount == FIRST_ARG) {
    if (synType == VARIABLE_ENTITY) {
      patternArg.push_back(
          std::move(std::make_unique<SynonymArg>(curr.getValue())));
    } else {
      throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_VAR_SYN);
    }
  }
}

// TODO(QPS): part of refactoring in ms2
void AssignPatternParserState::processLastArgument() {
  if (patternArg.size() == 1 &&
      partialMatchWildCardCount == 1) {  // secondArg = _
    patternArg.push_back(std::move(std::make_unique<Wildcard>()));
  } else if ((patternArg.size() == maxNumberOfArgs &&
              partialMatchWildCardCount == 0)  // secondArg = exact
             || (partialMatchWildCardCount == 2 &&
                 patternArg.size() == maxNumberOfArgs)) {  // secondArg = _"x"_
    return;
  } else {
    throw QPSInvalidQueryException(
        QPS_INVALID_QUERY_INCOMPLETE_PARTIAL_MATCH_PATTERN);
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
        outerSynonym = make_unique<SynonymArg>(curr.getValue());
        break;
      case PQL_COMMA_TOKEN:
        argumentCount++;
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
        parserContext.addClause(make_unique<PatternClause>(
            std::move(outerSynonym), std::move(patternArg),
            partialMatchWildCardCount == 2));
        break;
      case PQL_WILDCARD_TOKEN:
        if (argumentCount > 0) {
          partialMatchWildCardCount++;
        } else {
          patternArg.push_back(std::move(std::make_unique<Wildcard>()));
        }
        break;
      case PQL_LITERAL_REF_TOKEN:
        patternArg.push_back(
            std::move(std::make_unique<Ident>(curr.getValue())));
        break;
      case PQL_SUCH_TOKEN:
        this->parserContext.transitionTo(
            make_unique<SuchThatParserState>(parserContext));
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
