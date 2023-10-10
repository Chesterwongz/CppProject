#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/cfg/CFG.h"

class MockCFG : public CFG {
 public:
  explicit MockCFG(IntToIntSetMap adjList, IntToIntSetMap reversedAdjList)
      : CFG(std::move(adjList), std::move(reversedAdjList)){};
};
