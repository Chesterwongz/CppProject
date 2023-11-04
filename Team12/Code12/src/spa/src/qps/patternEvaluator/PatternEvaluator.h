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

using std::string, std::vector, std::unique_ptr, std::set, std::pair;

class PatternEvaluator {
 protected:
  AbstractArgument& firstArg;
  PKBReader& pkbReader;
  string synonymValue;

 public:
  explicit PatternEvaluator(AbstractArgument& firstArg,
                            PKBReader& pkbReader, string synonymValue)
      : firstArg(firstArg),
        pkbReader(pkbReader),
        synonymValue(std::move(synonymValue)) {}

  virtual IntermediateTable evaluate();
  virtual vector<pair<string, string>> evaluateArguments() = 0;
  virtual IntermediateTable buildResultTable(
      const vector<pair<string, string>>& pkbResult);
  virtual ~PatternEvaluator() = default;
};
