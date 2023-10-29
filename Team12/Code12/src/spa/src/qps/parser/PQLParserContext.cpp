#include "PQLParserContext.h"

#include <utility>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/common/QPSStringUtils.h"

PQLParserContext::PQLParserContext(unique_ptr<PQLTokenStream> tokenStream,
                                   unique_ptr<Query>& query)
    : tokenStream(std::move(tokenStream)),
      query(query),
      currState(),
      context(std::make_unique<SynonymContext>()) {}

void PQLParserContext::addToContext(string entity, const string& synonym) {
  bool isSuccess = this->context->addSynonym(synonym, std::move(entity));
  if (!isSuccess) isSemanticallyValid = false;
}

void PQLParserContext::addSelectClause() {
  this->query->setSynonymToQuery({});
}

void PQLParserContext::addSelectClause(unique_ptr<SynonymArg> synonym) {
  SynonymsToSelect synonymVector = {};
  synonymVector.emplace_back(std::move(synonym));
  this->query->setSynonymToQuery(std::move(synonymVector));
}

void PQLParserContext::addSelectClause(SynonymsToSelect synonyms) {
  this->query->setSynonymToQuery(std::move(synonyms));
}

string PQLParserContext::getValidSynonymType(const string& synonym) {
  auto entity = context->getTokenEntity(synonym);
  if (entity.has_value()) {
    return entity.value();
  }
  isSemanticallyValid = false;
  return "";
}

bool PQLParserContext::checkSynonymExists(const std::string& synonym) {
  return context->checkIfSynonymExists(synonym);
}

void PQLParserContext::addClause(unique_ptr<Clause> clause) {
  query->addClause(std::move(clause));
}

void PQLParserContext::setSemanticallyInvalid() { isSemanticallyValid = false; }

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

std::optional<PQLToken> PQLParserContext::peekNextToken() {
  return tokenStream->peek();
}

void PQLParserContext::transitionTo(unique_ptr<IParserState> nextState) {
  currState = std::move(nextState);
}

void PQLParserContext::handleTokens() {
  while (tokenStream->peek().has_value()) {
    currState->handleToken();
  }
  if (!isSemanticallyValid) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR);
  }
}
