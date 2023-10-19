#include <utility>

#include "SynonymContext.h"
#include "qps/exceptions/QPSSemanticError.h"

Entity SynonymContext::getTokenEntity(const Synonym &synonym) {
  auto entity = tokenNameToTokenMap.find(synonym);

  if (entity == tokenNameToTokenMap.end()) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_UNDECLARED_SYNONYM + synonym);
  }

  return entity->second;
}

bool SynonymContext::checkIfSynonymExists(const Synonym &tokenName) {
  auto entity = tokenNameToTokenMap.find(tokenName);

  return entity != tokenNameToTokenMap.end();
}

void SynonymContext::addSynonym(const Synonym &tokenSynonym, Entity tokenEntity) {
  if (tokenNameToTokenMap.find(tokenSynonym) != tokenNameToTokenMap.end()) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_REPEATED_SYNONYM);
  }
  this->tokenNameToTokenMap[tokenSynonym] = std::move(tokenEntity);
}
