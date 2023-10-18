#pragma once

#include <unordered_map>

#include "RelationTStore.h"

class NextStore : public RelationTStore<int> {
 protected:
  void precomputeRelationT(int from, int to) override;
  void computeSuccessorsT(int from) override;
  void computeAncestorsT(int to) override;
  void computeAllRelationsT() override;

 public:
  void clearCache() override;
};
