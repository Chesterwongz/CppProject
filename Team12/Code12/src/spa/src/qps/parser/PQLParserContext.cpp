#include "PQLParserContext.h"

#include <utility>

#include "qps/common/QPSStringUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLParserContext::PQLParserContext(unique_ptr<PQLTokenStream> tokenStream,
                                   unique_ptr<Query>& query)
    : tokenStream(std::move(tokenStream)),
      query(query),
      currState(),
      context(std::make_unique<Context>()) {}

void PQLParserContext::addToContext(string entity, const string& synonym) {
  if (!QPSStringUtils::isSynonym(synonym)) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
  }
  this->context->addSynonym(synonym, std::move(entity));
}

void PQLParserContext::addSelectSynonym(const string& synonym) {
  getValidSynonymType(synonym);
  this->query->setSynonymToQuery(synonym);
}

void PQLParserContext::addSelectClause(
    vector<unique_ptr<AbstractArgument>> synonyms) {
  // TODO(@teoyuqi): create the select clause here and add the synonyms
}

string PQLParserContext::getValidSynonymType(const string& synonym) {
  auto selectSynonym = context->getTokenEntity(synonym);
  return selectSynonym;
}

void PQLParserContext::addClause(unique_ptr<Clause> clause) {
  query->addClause(std::move(clause));
}

bool PQLParserContext::isExpectedToken(PQLTokenType curr, PQLTokenType prev,
                                       PredictiveMap& pm) {
  auto nextPair = pm.find(prev);
  if (nextPair == pm.end()) return false;

  auto nextToken = nextPair->second;
  return nextToken.find(curr) != nextToken.end();
}

std::optional<PQLToken> PQLParserContext::eatExpectedToken(PQLTokenType prev,
                                                           PredictiveMap& pm) {
  std::optional<PQLToken> tokenOpt = tokenStream->eat();
  if (!tokenOpt.has_value()) return std::nullopt;

  if (tokenOpt->getType() == PQL_NAME_TOKEN) {
    currState->processNameToken(tokenOpt.value());
  }

  if (!isExpectedToken(tokenOpt->getType(), prev, pm)) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR + tokenOpt->getValue());
  }

  return tokenOpt;
}

void PQLParserContext::transitionTo(unique_ptr<IParserState> nextState) {
  currState = std::move(nextState);
}

void PQLParserContext::handleTokens() {
  while (tokenStream->peek().has_value()) {
    currState->handleToken();
  }
  query->addContext(std::move(context));
}
