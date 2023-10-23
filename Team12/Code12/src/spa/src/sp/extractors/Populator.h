#pragma once

#include <memory>
#include <vector>

#include "common/ast/TNode.h"

class Populator {
 public:
  Populator();
  void populate(TNode& node,
                const std::vector<std::unique_ptr<Extractor>>& extractorVector);
};
