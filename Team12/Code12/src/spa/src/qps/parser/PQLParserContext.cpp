#include "PQLParserContext.h"

#include <utility>
#include "qps/common/QPSStringUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLParserContext::PQLParserContext(PQLTokenStream& tokenStream, Query& query)
    : tokenStream(tokenStream),
      query(query),
      currState(),
      context(std::make_unique<Context>()) {}

PQLTokenStream& PQLParserContext::getTokenStream() const { return tokenStream; }

void PQLParserContext::transitionTo(unique_ptr<IParserState> nextState) {
  currState = std::move(nextState);
}

void PQLParserContext::addToContext(string entity, const string& synonym) {
  if (!QPSStringUtils::isSynonym(synonym)) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
  }
  this->context->addSynonym(synonym, std::move(entity));
}

void PQLParserContext::addClause(unique_ptr<Clause> clause) {
  query.addClause(std::move(clause));
}

void PQLParserContext::handleTokens() {
  while (!tokenStream.isTokenStreamEnd()) {
    currState->handleToken();
  }
  query.addContext(std::move(context));
}

void PQLParserContext::addSelectSynonym(const string& synonym) {
  checkValidSynonym(synonym);
  this->query.setSynonymToQuery(synonym);
}

string PQLParserContext::checkValidSynonym(const string& synonym) {
  auto selectSynonym = context->getTokenEntity(synonym);
  return selectSynonym;
}
