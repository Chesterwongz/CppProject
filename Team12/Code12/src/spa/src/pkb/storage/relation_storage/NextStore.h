#pragma once

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

#include "RelationTStore.h"

class NextStore : public RelationTStore<int> {
 public:
  void clearCache() override;
};
