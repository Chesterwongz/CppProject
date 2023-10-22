#include "SynonymContext.h"

#include <utility>

std::optional<Entity> SynonymContext::getTokenEntity(const Synonym &synonym) {
  auto entity = tokenNameToTokenMap.find(synonym);

  if (entity == tokenNameToTokenMap.end()) {
    return std::nullopt;
  }

  return entity->second;
}

bool SynonymContext::checkIfSynonymExists(const Synonym &tokenName) {
  auto entity = tokenNameToTokenMap.find(tokenName);

  return entity != tokenNameToTokenMap.end();
}

bool SynonymContext::addSynonym(const Synonym &tokenSynonym,
                                Entity tokenEntity) {
  if (tokenNameToTokenMap.find(tokenSynonym) != tokenNameToTokenMap.end()) {
    return false;
  }
  this->tokenNameToTokenMap[tokenSynonym] = std::move(tokenEntity);
  return true;
}
