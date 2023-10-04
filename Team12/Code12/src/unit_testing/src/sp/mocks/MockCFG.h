#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/cfg/CFG.h"

class MockCFG : public CFG {
 public:
  explicit MockCFG(unordered_map<int, unordered_set<int>> adjList,
                   unordered_map<int, unordered_set<int>> reversedAdjList)
      : CFG(std::move(adjList), std::move(reversedAdjList)){};
};
