#pragma once

#include <string>

#include "RelationTStore.h"

class CallsSStore : public RelationStore<int, std::string> {
 public:
  [[nodiscard]] const std::unordered_map<int, std::unordered_set<std::string>>& getCallsSMap() const {
    return directSuccessorMap;
  }
};
