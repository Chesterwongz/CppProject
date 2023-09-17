#include "Context.h"

#include "qps/exceptions/QPSInvalidQueryException.h"

Entity Context::getTokenEntity(Synonym synonym) {
    auto entity = tokenNameToTokenMap.find(synonym);

    if (syn == tokenNameToTokenMap.end()) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
    }

    return entity;
};

void Context::addToken(Synonym tokenSynonym, Entity tokenEntity) {
    this->tokenNameToTokenMap[tokenSynonym] = tokenEntity;
};
