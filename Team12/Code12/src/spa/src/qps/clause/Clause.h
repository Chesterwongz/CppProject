#pragma once

#include <set>
#include <string>
#include <unordered_set>

#include "pkb/facade/PKBReader.h"
#include "qps/context/Context.h"
#include "qps/intermediateTable/IntermediateTable.h"

using std::string, std::set, std::map, std::pair, std::vector;

class Clause {
 public:
  virtual IntermediateTable evaluate(Context& context, PKBReader& pkb) = 0;
  virtual ~Clause() = default;
  virtual bool isEquals(const Clause& other) = 0;
};
