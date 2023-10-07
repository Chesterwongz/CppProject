#include "Context.h"

#include <utility>

#include "qps/exceptions/QPSSemanticError.h"

Entity Context::getTokenEntity(const Synonym &synonym) {
  auto entity = tokenNameToTokenMap.find(synonym);

  if (entity == tokenNameToTokenMap.end()) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_UNDECLARED_SYNONYM + synonym);
  }

  return entity->second;
}

void Context::addSynonym(const Synonym &tokenSynonym, Entity tokenEntity) {
  if (tokenNameToTokenMap.find(tokenSynonym) != tokenNameToTokenMap.end()) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_REPEATED_SYNONYM);
  }
  this->tokenNameToTokenMap[tokenSynonym] = std::move(tokenEntity);
}

unordered_map<Synonym, Entity> &Context::getMap() {
  return tokenNameToTokenMap;
}
