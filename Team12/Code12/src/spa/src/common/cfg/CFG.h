#pragma once

#include <utility>

#include "common/AliasTypes.h"

class CFG {
 private:
  IntToIntSetMap adjList;
  IntToIntSetMap reversedAdjList;

 protected:
  explicit CFG(IntToIntSetMap adjList, IntToIntSetMap reversedAdjList);

 public:
  CFG();
  void addEdge(int from, int to);
  bool operator==(const CFG& other) const;
  [[nodiscard]] const IntToIntSetMap& getAdjList() const;
};
