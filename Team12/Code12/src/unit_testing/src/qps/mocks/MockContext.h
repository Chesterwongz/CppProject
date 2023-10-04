#pragma once

#include "../../../../spa/src/qps/context/Context.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

using std::string, std::unordered_map;

typedef string Synonym;
typedef string Entity;

class MockContext : public Context {
 public:
  unordered_map<Synonym, Entity> mockTokenNameToTokenMap = {};
  Entity mockTokenEntity;
  Synonym mockTokenSynonym;

  Entity getTokenEntity(const Synonym& tokenName) override {
    return mockTokenEntity;
  }

  unordered_map<Synonym, Entity>& getMap() override {
    return mockTokenNameToTokenMap;
  }
};
