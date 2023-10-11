#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/patternEvaluator/PatternEvaluator.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"

using std::string, std::unique_ptr, std::vector;

class PatternClause : public Clause {
 private:
  unique_ptr<AbstractArgument> synonym;
  PatternArgsStream patternArgsStream;
  bool isPartialMatch;

 public:
  explicit PatternClause(unique_ptr<AbstractArgument> synonym,
                         PatternArgsStream patternArgsStream,
                         bool isPartialMatch)
      : synonym(std::move(synonym)),
        patternArgsStream(std::move(patternArgsStream)),
        isPartialMatch(isPartialMatch) {}
  explicit PatternClause(unique_ptr<AbstractArgument> synonym,
                         PatternArgsStream patternArgsStream)
      : synonym(std::move(synonym)),
        patternArgsStream(std::move(patternArgsStream)),
        isPartialMatch(false) {}

  IntermediateTable evaluate(Context& context, PKBReader& pkb) override;
  bool isEquals(const Clause& other) override;
};
