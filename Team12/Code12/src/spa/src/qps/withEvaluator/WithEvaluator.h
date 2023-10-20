#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <functional>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/clause/withClause/WithClauseUtils.h"

using std::string, std::vector, std::unique_ptr, std::set, std::pair, std::move, std::function;

typedef function<IntermediateTable(PKBReader& pkbReader)> WithEvaluatorFunc;

class WithEvaluator {
 protected:
  virtual IntermediateTable evaluateStmtNum(PKBReader& pkbReader);
  virtual IntermediateTable evaluateConstantValue(PKBReader& pkbReader);
  virtual IntermediateTable evaluateProcName(PKBReader& pkbReader);
  virtual IntermediateTable evaluateVarName(PKBReader& pkbReader);
  virtual IntermediateTable evaluateCallProcName(PKBReader& pkbReader);
  virtual IntermediateTable evaluateCallStmtNum(PKBReader& pkbReader);
  virtual IntermediateTable evaluateReadVarName(PKBReader& pkbReader);
  virtual IntermediateTable evaluateReadStmtNum(PKBReader& pkbReader);
  virtual IntermediateTable evaluatePrintVarName(PKBReader& pkbReader);
  virtual IntermediateTable evaluatePrintStmtNum(PKBReader& pkbReader);

  unordered_map<Entity_AttrRef_Permutation, WithEvaluatorFunc>
      withEvaluatorFuncMap {
          {Entity_AttrRef_Permutation::STMT_STMTNUM,
           [this](PKBReader& pkbReader) { 
              return evaluateStmtNum(pkbReader); 
          }},
          {Entity_AttrRef_Permutation::READ_STMTNUM,
           [this](PKBReader& pkbReader) {
             return evaluateReadStmtNum(pkbReader);
           }},
          {Entity_AttrRef_Permutation::PRINT_STMTNUM,
           [this](PKBReader& pkbReader) {
             return evaluatePrintStmtNum(pkbReader);
           }},
          {Entity_AttrRef_Permutation::CALL_STMTNUM,
           [this](PKBReader& pkbReader) {
             return evaluateCallStmtNum(pkbReader);
           }},
          {Entity_AttrRef_Permutation::WHILE_STMTNUM,
           [this](PKBReader& pkbReader) { 
              return evaluateStmtNum(pkbReader); 
          }},
          {Entity_AttrRef_Permutation::IF_STMTNUM,
           [this](PKBReader& pkbReader) { 
              return evaluateStmtNum(pkbReader); 
          }},
          {Entity_AttrRef_Permutation::ASSIGN_STMTNUM,
           [this](PKBReader& pkbReader) { 
              return evaluateStmtNum(pkbReader); 
          }},
          {Entity_AttrRef_Permutation::READ_VARNAME,
           [this](PKBReader& pkbReader) {
             return evaluateReadVarName(pkbReader);
           }},
          {Entity_AttrRef_Permutation::VAR_VARNAME,
           [this](PKBReader& pkbReader) { 
              return evaluateVarName(pkbReader); 
          }},
          {Entity_AttrRef_Permutation::PRINT_VARNAME,
           [this](PKBReader& pkbReader) {
             return evaluatePrintVarName(pkbReader);
           }},
          {Entity_AttrRef_Permutation::PROCEDURE_PROCNAME,
           [this](PKBReader& pkbReader) {
             return evaluateProcName(pkbReader);
           }},
          {Entity_AttrRef_Permutation::CALL_PROCNAME,
           [this](PKBReader& pkbReader) {
             return evaluateCallProcName(pkbReader);
           }},
          {Entity_AttrRef_Permutation::CONSTANT_VALUE,
           [this](PKBReader& pkbReader) {
             return evaluateConstantValue(pkbReader);
           }}};
 public:
  virtual IntermediateTable evaluate(PKBReader& pkbReader) = 0;

  virtual ~WithEvaluator() = default;
};
