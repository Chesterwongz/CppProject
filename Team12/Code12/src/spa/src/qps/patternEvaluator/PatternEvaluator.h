#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/context/Context.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set;

typedef vector<unique_ptr<AbstractArgument>> PatternArgsStream;

class PatternEvaluator {
 protected:
  PatternArgsStream& patternArgsStream;
  PKBReader& pkbReader;
  bool isPartialMatch;
  string synonymValue;

 public:
  explicit PatternEvaluator(PatternArgsStream& patternArgsStream,
                            PKBReader& pkbReader, bool isPartialMatch,
                            string synonymValue)
      : patternArgsStream(patternArgsStream),
        pkbReader(pkbReader),
        isPartialMatch(isPartialMatch),
        synonymValue(synonymValue) {}
  virtual IntermediateTable evaluate();
  virtual IntermediateTable buildResultTable(vector<string> pkbResult);
  virtual vector<string> processArguments() = 0;
  virtual ~PatternEvaluator() = default;
};
