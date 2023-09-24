#pragma once

#include <string>
#include <utility>
#include <unordered_set>

#include "qps/clause/Clause.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/IArgument.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/patternEvaluator/IPatternEvaluator.h"

using std::string, std::unique_ptr, std::vector;

class PatternClause : public Clause {
private:
    unique_ptr<IArgument> synonym;
    PatternArgsStreamPtr patternArgsStreamPtr;
    bool isPartialMatch;

public:
    // prolly will have to add one more field that specifies if the pattern arg is a direct or partial match
    explicit PatternClause(unique_ptr<IArgument> synonym,
                           PatternArgsStreamPtr patternArgsStreamPtr,
                           bool isPartialMatch);

    IntermediateTable evaluate(
            Context& context,
            PKBReader &pkb) override;
    bool isEquals(const Clause& other) override;
};