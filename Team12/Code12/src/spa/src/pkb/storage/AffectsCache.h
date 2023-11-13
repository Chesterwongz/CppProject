#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "pkb/storage/relation_storage/RelationTStore.h"

class AffectsCache : public RelationStore<int, int> {
 private:
  bool isComplete = false;

 public:
  void clearCache() override;
  void setIsComplete();
  bool getIsComplete();
};
