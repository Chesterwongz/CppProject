#pragma once

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set, std::pair, std::move,
    std::function;

typedef function<vector<SynonymRes>()> WithEvaluatorFunc;

class WithEvaluator {
 protected:
  PKBReader& pkbReader;

  virtual vector<SynonymRes> evaluateStmtEntity();
  virtual vector<SynonymRes> evaluateAssignEntity();
  virtual vector<SynonymRes> evaluateIfEntity();
  virtual vector<SynonymRes> evaluateWhileEntity();
  virtual vector<SynonymRes> evaluateConstantEntity();
  virtual vector<SynonymRes> evaluateProcEntity();
  virtual vector<SynonymRes> evaluateVarEntity();
  virtual vector<SynonymRes> evaluateCallEntity();
  virtual vector<SynonymRes> evaluateReadEntity();
  virtual vector<SynonymRes> evaluatePrintEntity();

  vector<SynonymRes> buildStmtSynonymResVector(vector<string> stmtNums);
  vector<SynonymRes> buildConstantSynonymResVector(vector<string> constantVals);
  vector<SynonymRes> buildProcSynonymResVector(vector<string> procNames);
  vector<SynonymRes> buildVarSynonymResVector(vector<string> procNames);
  vector<SynonymRes> buildCallSynonymResVector(
      vector<pair<string, string>> callProcNamePairs);
  vector<SynonymRes> buildReadSynonymResVector(
      vector<pair<string, string>> readVarNamePairs);
  vector<SynonymRes> buildPrintSynonymResVector(
      vector<pair<string, string>> printVarNamePairs);

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
      {CONSTANT_ENTITY, [this]() { return evaluateConstantEntity(); }}

  };
 public:
  explicit WithEvaluator(PKBReader& pkbReader)
      : pkbReader(pkbReader) {}

  virtual IntermediateTable evaluate() = 0;

  virtual ~WithEvaluator() = default;
};
