#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set, std::pair, std::move;

class IWithEvaluator {
 public:
  virtual IntermediateTable evaluate(PKBReader& pkbReader) = 0;

  virtual ~IWithEvaluator() = default;
};
