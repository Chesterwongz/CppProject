#include "PQLParserContext.h"

#include <utility>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/selectClause/SelectClause.h"
#include "qps/common/QPSStringUtils.h"

PQLParserContext::PQLParserContext(unique_ptr<PQLTokenStream> tokenStream,
                                   unique_ptr<Query>& query)
    : tokenStream(std::move(tokenStream)),
      query(query),
      currState(),
      context(std::make_unique<Context>()) {}

void PQLParserContext::addToContext(string entity, const string& synonym) {
  if (!QPSStringUtils::isSynonym(synonym)) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_NAME);
  }
  this->context->addSynonym(synonym, std::move(entity));
}

void PQLParserContext::addSelectClause(const string& synonym) {
  getValidSynonymType(synonym);
  SynonymsToSelect synonymVector = {};
  unique_ptr<SynonymArg> synonymArg
      = std::make_unique<SynonymArg>(synonym);
  synonymVector.emplace_back(std::move(synonymArg));
  this->query->setSynonymToQuery(std::move(synonymVector));
}

void PQLParserContext::addSelectClause(
    SynonymsToSelect synonyms) {
  this->query->setSynonymToQuery(std::move(synonyms));
}

string PQLParserContext::getValidSynonymType(const string& synonym) {
  auto selectSynonym = context->getTokenEntity(synonym);
  return selectSynonym;
}

bool PQLParserContext::checkSynonymExists(const std::string& synonym) {
  return context->checkIfSynonymExists(synonym);
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

std::optional<PQLToken> PQLParserContext::eatCurrToken() {
  return tokenStream->eat();
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
