#pragma once

#include "../../../../spa/src/qps/context/Context.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

using std::string, std::unordered_map;

typedef string Synonym;
typedef string Entity;

class MockContext : public Context{
public:
    unordered_map<Synonym, Entity> mockTokenNameToTokenMap = {};
    Entity mockTokenEntity;
    Synonym mockTokenSynonym;

    void addSynonym(const Synonym& tokenSynonym, Entity tokenEntity) {
        if (mockTokenNameToTokenMap.find(tokenSynonym) != mockTokenNameToTokenMap.end()) {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_REPEAT_SYNONYM_NAME);
        }
        this->mockTokenNameToTokenMap[tokenSynonym] = std::move(tokenEntity);
    }


    Entity getTokenEntity(const Synonym& tokenName) {
        return mockTokenEntity;
    }

    Synonym getTokenSynonym() {
        return mockTokenSynonym;
    }
    
    unordered_map<Synonym, Entity>& getMap() {
        return mockTokenNameToTokenMap;
    }
};