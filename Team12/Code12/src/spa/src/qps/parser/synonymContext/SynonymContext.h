#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "qps/common/Keywords.h"

using std::string, std::unordered_map;

class SynonymContext {
 private:
  unordered_map<Synonym, Entity> tokenNameToTokenMap = {};

 public:
  virtual bool addSynonym(const Synonym& tokenSynonym, Entity tokenEntity);
  virtual std::optional<Entity> getTokenEntity(const Synonym& tokenName);
  virtual bool checkIfSynonymExists(const Synonym& tokenName);
};
