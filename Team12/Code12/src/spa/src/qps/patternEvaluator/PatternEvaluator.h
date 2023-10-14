#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/context/Context.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set;

typedef vector<unique_ptr<AbstractArgument>> PatternArgsStream;

class PatternEvaluator {
 protected:
  unique_ptr<AbstractArgument> firstArg;
  PKBReader& pkbReader;
  bool isPartialMatch;
  string synonymValue;

 public:
  explicit PatternEvaluator(unique_ptr<AbstractArgument> firstArg,
                            PKBReader& pkbReader, bool isPartialMatch,
                            string synonymValue)
      : firstArg(std::move(firstArg)),
        pkbReader(pkbReader),
        isPartialMatch(isPartialMatch),
        synonymValue(synonymValue) {}

  explicit PatternEvaluator(unique_ptr<AbstractArgument> firstArg,
                            PKBReader& pkbReader, string synonymValue)
      : firstArg(std::move(firstArg)),
        pkbReader(pkbReader),
        isPartialMatch(false),
        synonymValue(synonymValue) {}

  virtual IntermediateTable evaluate();
  virtual vector<std::pair<string, string>> processArguments() = 0;
  virtual IntermediateTable buildResultTable(
      vector<std::pair<string, string>> pkbResult);
  virtual ~PatternEvaluator() = default;
};
