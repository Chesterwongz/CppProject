#include "SuchThatParserState.h"

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/relationshipParserState/followsParserState/FollowsParserState.h"
#include "qps/parser/relationshipParserState/modifiesParserState/ModifiesParserState.h"
#include "qps/parser/relationshipParserState/parentsParserState/ParentsParserState.h"
#include "qps/parser/relationshipParserState/usesParserState/UsesParserState.h"

PredictiveMap SuchThatParserState::predictiveMap = {
    {PQL_NULL_TOKEN, {PQL_SUCH_TOKEN}},
    {PQL_SUCH_TOKEN, {PQL_THAT_TOKEN}},
    {PQL_THAT_TOKEN,
     {PQL_FOLLOWS_TOKEN, PQL_PARENT_TOKEN, PQL_USES_TOKEN,
      PQL_MODIFIES_TOKEN}}};

SuchThatParserState::SuchThatParserState(PQLParserContext &parserContext)
    : parserContext(parserContext),
      tokenStream(parserContext.getTokenStream()),
      prev(PQL_NULL_TOKEN){};

void SuchThatParserState::processNameToken(PQLToken &curr) {
  auto tokenType = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
  curr.updateTokenType(tokenType);
}

void SuchThatParserState::handleToken() {
  while (!this->tokenStream.isTokenStreamEnd()) {
    auto &curr = tokenStream.getCurrentToken();

    if (curr.getType() == PQL_NAME_TOKEN) {
      processNameToken(curr);
    }

    if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
      throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
    }
    switch (curr.getType()) {
      case PQL_SUCH_TOKEN:
      case PQL_THAT_TOKEN:
        break;
      case PQL_FOLLOWS_TOKEN:
        parserContext.transitionTo(
            make_unique<FollowsParserState>(parserContext));
        return;
      case PQL_PARENT_TOKEN:
        parserContext.transitionTo(
            make_unique<ParentsParserState>(parserContext));
        return;
      case PQL_USES_TOKEN:
        parserContext.transitionTo(make_unique<UsesParserState>(parserContext));
        return;
      case PQL_MODIFIES_TOKEN:
        parserContext.transitionTo(
            make_unique<ModifiesParserState>(parserContext));
        return;
      default:
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
    }
    this->prev = curr.getType();
    tokenStream.next();
  }
  // should never exit in this parser
  throw QPSInvalidQueryException(QPS_INVALID_QUERY_INCOMPLETE_QUERY);
}
