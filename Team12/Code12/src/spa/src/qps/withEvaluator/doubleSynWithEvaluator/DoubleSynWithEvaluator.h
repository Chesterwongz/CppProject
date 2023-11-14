#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/withEvaluator/WithEvaluator.h"

using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
    std::function, std::make_unique;

class DoubleSynWithEvaluator : public WithEvaluator {
 protected:
  SynonymArg& firstSynonymArg;
  SynonymArg& secondSynonymArg;

 public:
  explicit DoubleSynWithEvaluator(SynonymArg& firstArg,
                                  SynonymArg& secondArg,
                                  PKBReader& pkbReader)
      : WithEvaluator(pkbReader),
        firstSynonymArg(firstArg),
        secondSynonymArg(secondArg) {}

  IntermediateTable evaluate() override;
};
