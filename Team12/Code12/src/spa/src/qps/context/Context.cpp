#include "Context.h"

#include <utility>

#include "qps/exceptions/QPSInvalidQueryException.h"

Entity Context::getTokenEntity(const Synonym &synonym) {
    auto entity = tokenNameToTokenMap.find(synonym);

    if (entity == tokenNameToTokenMap.end()) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
    }

    return entity->second;
};

void Context::addSynonym(const Synonym& tokenSynonym, Entity tokenEntity) {
    if (tokenNameToTokenMap.find(tokenSynonym) != tokenNameToTokenMap.end()) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_REPEAT_SYNONYM_NAME);
    }
    this->tokenNameToTokenMap[tokenSynonym] = std::move(tokenEntity);
}

unordered_map<Synonym, Entity> &Context::getMap() {
    return tokenNameToTokenMap;
}
