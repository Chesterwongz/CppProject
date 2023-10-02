#pragma once

#include <utility>

#include "common/cfg/CFG.h"

class MockCFG : public CFG {
public:
    explicit MockCFG(unordered_map<int, vector<int>> adjList) : CFG(std::move(adjList)) {};
};