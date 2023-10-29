#pragma once

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "qps/queryEvaluator/utils/clauseGroup/ClauseGroup.h"
#include "qps/queryEvaluator/utils/clauseGroupQueue/ClauseGroupQueue.h"

using std::vector, std::unique_ptr, std::unordered_map, std::string;

class IClauseGrouper {
 public:
  virtual ClauseGroupQueue groupClauses() = 0;
  virtual ~IClauseGrouper() = default;
};
