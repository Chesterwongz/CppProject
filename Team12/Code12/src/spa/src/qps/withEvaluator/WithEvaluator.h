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
#include "qps/clause/utils/ClauseUtil.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::vector, std::unique_ptr, std::set, std::pair, std::move,
    std::function;

typedef function<vector<std::reference_wrapper<SynonymRes>>()>
    WithEvaluatorFunc;

class WithEvaluator {
 protected:
  PKBReader& pkbReader;
  unordered_map<Entity, WithEvaluatorFunc> withEvaluatorFuncMap = {
      {ASSIGN_ENTITY,
       [this]() { return ClauseUtil::getAllAssignStmts(pkbReader); }},
      {IF_ENTITY, [this]() { return ClauseUtil::getAllIfStmts(pkbReader); }},
      {WHILE_ENTITY,
       [this]() { return ClauseUtil::getAllWhileStmts(pkbReader); }},
      {STMT_ENTITY, [this]() { return ClauseUtil::getAllStmts(pkbReader); }},
      {READ_ENTITY,
       [this]() { return ClauseUtil::getAllReadStmts(pkbReader); }},
      {PRINT_ENTITY,
       [this]() { return ClauseUtil::getAllPrintStmts(pkbReader); }},
      {CALL_ENTITY,
       [this]() { return ClauseUtil::getAllCallStmts(pkbReader); }},
      {VARIABLE_ENTITY,
       [this]() { return ClauseUtil::getAllVariables(pkbReader); }},
      {PROCEDURE_ENTITY,
       [this]() { return ClauseUtil::getAllProcedures(pkbReader); }},
      {CONSTANT_ENTITY,
       [this]() { return ClauseUtil::getAllConstants(pkbReader); }}};

 public:
  explicit WithEvaluator(PKBReader& pkbReader) : pkbReader(pkbReader) {}

  virtual IntermediateTable evaluate() = 0;

  virtual ~WithEvaluator() = default;
};
