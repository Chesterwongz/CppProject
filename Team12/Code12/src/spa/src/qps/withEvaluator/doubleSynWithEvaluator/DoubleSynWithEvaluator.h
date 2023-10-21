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
  unique_ptr<SynonymArg> firstSynonymArg;
  unique_ptr<SynonymArg> secondSynonymArg;

 public:
  explicit DoubleSynWithEvaluator(unique_ptr<SynonymArg> firstArg,
                                  unique_ptr<SynonymArg> secondArg,
                                  PKBReader& pkbReader)
      : WithEvaluator(pkbReader),
        firstSynonymArg(move(firstArg)),
        secondSynonymArg(move(secondArg)) {}

  IntermediateTable evaluate() override;
};
