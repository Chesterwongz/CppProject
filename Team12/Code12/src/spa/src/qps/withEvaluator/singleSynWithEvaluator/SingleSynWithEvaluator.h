#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/withEvaluator/WithEvaluator.h"

using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
    std::function, std::make_unique;

class SingleSynWithEvaluator : public WithEvaluator {
 protected:
  SynonymArg& synonymArg;
  AbstractArgument& valueArg;

  vector<std::reference_wrapper<SynonymRes>> evaluateStmtEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateAssignEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateIfEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateWhileEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateConstantEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateProcEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateVarEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateCallEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluateReadEntity() override;
  vector<std::reference_wrapper<SynonymRes>> evaluatePrintEntity() override;

  vector<std::reference_wrapper<SynonymRes>> evaluateStmtTypes(
      StmtType stmtType);

 public:
  explicit SingleSynWithEvaluator(SynonymArg& firstArg,
                                  AbstractArgument& secondArg,
                                  PKBReader& pkbReader)
      : WithEvaluator(pkbReader), synonymArg(firstArg), valueArg(secondArg) {}

  IntermediateTable evaluate() override;
};
