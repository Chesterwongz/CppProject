#pragma once

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set, std::pair, std::move,
    std::function;

typedef function<vector<std::reference_wrapper<SynonymRes>>()>
    WithEvaluatorFunc;

class WithEvaluator {
 protected:
  PKBReader& pkbReader;

  virtual vector<std::reference_wrapper<SynonymRes>> evaluateStmtEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateAssignEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateIfEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateWhileEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateConstantEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateProcEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateVarEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateCallEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluateReadEntity();
  virtual vector<std::reference_wrapper<SynonymRes>> evaluatePrintEntity();

  unordered_map<Entity, WithEvaluatorFunc> withEvaluatorFuncMap = {
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
  explicit WithEvaluator(PKBReader& pkbReader) : pkbReader(pkbReader) {}

  virtual IntermediateTable evaluate() = 0;

  virtual ~WithEvaluator() = default;
};
