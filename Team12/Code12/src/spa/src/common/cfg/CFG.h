#pragma once

#include <utility>

#include "common/AliasTypes.h"

class CFG {
 private:
  IntToIntSetMap adjList;

 protected:
  explicit CFG(IntToIntSetMap adjList);

 public:
  CFG();
  void addEdge(int from, int to);
  bool operator==(const CFG& other) const;
  [[nodiscard]] const IntToIntSetMap& getAdjList() const;
};
