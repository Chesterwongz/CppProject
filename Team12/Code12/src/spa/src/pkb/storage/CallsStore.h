#pragma once

#include <string>

#include "RelationTStore.h"

class CallsStore : public RelationTStore<std::string, std::string> {
 public:
  [[nodiscard]] const std::unordered_map<std::string, std::unordered_set<std::string>>& getCallsPMap() const {
    return transitiveSuccessorMap;
  }
};
