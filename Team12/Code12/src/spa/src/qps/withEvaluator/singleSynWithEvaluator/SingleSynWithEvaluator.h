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

typedef function<vector<std::reference_wrapper<SynonymRes>>()>
    SingleSynWithEvaluatorFunc;

class SingleSynWithEvaluator : public WithEvaluator {
 protected:
  SynonymArg& synonymArg;
  AbstractArgument& valueArg;

  vector<std::reference_wrapper<SynonymRes>> evaluateStmtEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateAssignEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateIfEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateWhileEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateConstantEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateProcEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateVarEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateCallEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluateReadEntity();
  vector<std::reference_wrapper<SynonymRes>> evaluatePrintEntity();

  vector<std::reference_wrapper<SynonymRes>> evaluateStmtTypes(
      StmtType stmtType);

  unordered_map<Entity, SingleSynWithEvaluatorFunc>
      singleSynWithEvaluatorFuncMap = {
          {ASSIGN_ENTITY, [this]() { return evaluateAssignEntity(); }},
          {IF_ENTITY, [this]() { return evaluateIfEntity(); }},
          {WHILE_ENTITY, [this]() { return evaluateWhileEntity(); }},
          {STMT_ENTITY, [this]() { return evaluateStmtEntity(); }},
          {READ_ENTITY, [this]() { return evaluateReadEntity(); }},
          {PRINT_ENTITY, [this]() { return evaluatePrintEntity(); }},
          {CALL_ENTITY, [this]() { return evaluateCallEntity(); }},
          {VARIABLE_ENTITY, [this]() { return evaluateVarEntity(); }},
          {PROCEDURE_ENTITY, [this]() { return evaluateProcEntity(); }},
          {CONSTANT_ENTITY, [this]() { return evaluateConstantEntity(); }}};

 public:
  explicit SingleSynWithEvaluator(SynonymArg& firstArg,
                                  AbstractArgument& secondArg,
                                  PKBReader& pkbReader)
      : WithEvaluator(pkbReader), synonymArg(firstArg), valueArg(secondArg) {}

  IntermediateTable evaluate() override;
};
