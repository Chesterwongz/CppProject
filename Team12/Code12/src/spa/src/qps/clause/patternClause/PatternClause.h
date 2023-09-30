#pragma once

#include <string>
#include <utility>
#include <unordered_set>

#include "qps/clause/Clause.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/patternEvaluator/PatternEvaluatorFactory.h"
#include "qps/patternEvaluator/PatternEvaluator.h"

using std::string, std::unique_ptr, std::vector;

class PatternClause : public Clause {
private:
    unique_ptr<AbstractArgument> synonym;
    PatternArgsStream patternArgsStream;
    bool isPartialMatch;

public:
    explicit PatternClause(unique_ptr<AbstractArgument> synonym,
        PatternArgsStream patternArgsStream,
        bool isPartialMatch) :
        synonym(std::move(synonym)),
        patternArgsStream(std::move(patternArgsStream)),
        isPartialMatch(isPartialMatch) {};

    IntermediateTable evaluate(
            Context& context,
            PKBReader &pkb) override;
    bool isEquals(const Clause& other) override;
};
