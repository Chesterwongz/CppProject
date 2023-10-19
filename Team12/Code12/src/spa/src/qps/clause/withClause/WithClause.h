#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"

using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
    std::function;

typedef function<IntermediateTable(PKBReader&)> WithEvaluatorFunc;

class WithClause : public Clause {
 protected:
  unique_ptr<AbstractArgument> synonym;
  string synonymEntity;
  string& attrRef;
  string& attrRefValue;

  IntermediateTable evaluateStmtNum(PKBReader& pkbReader);
  IntermediateTable evaluateConstantValue(PKBReader& pkbReader);
  IntermediateTable evaluateProcName(PKBReader& pkbReader);
  IntermediateTable evaluateVarName(PKBReader& pkbReader);
  IntermediateTable evaluateCallProcName(PKBReader& pkbReader);
  IntermediateTable evaluateCallStmtNum(PKBReader& pkbReader);
  IntermediateTable evaluateReadVarName(PKBReader& pkbReader);
  IntermediateTable evaluateReadStmtNum(PKBReader& pkbReader);
  IntermediateTable evaluatePrintVarName(PKBReader& pkbReader);
  IntermediateTable evaluatePrintStmtNum(PKBReader& pkbReader);

  // stmt# attrRef
  pair<string, string> stmt_stmtNum_pair =
      make_pair(STMT_ENTITY, STMTNUM_ATTRREF);
  pair<string, string> read_stmtNum_pair =
      make_pair(READ_ENTITY, STMTNUM_ATTRREF);
  pair<string, string> print_stmtNum_pair =
      make_pair(PRINT_ENTITY, STMTNUM_ATTRREF);
  pair<string, string> call_stmtNum_pair =
      make_pair(CALL_ENTITY, STMTNUM_ATTRREF);
  pair<string, string> while_stmtNum_pair =
      make_pair(WHILE_ENTITY, STMTNUM_ATTRREF);
  pair<string, string> if_stmtNum_pair = 
    make_pair(IF_ENTITY, STMTNUM_ATTRREF);
  pair<string, string> assign_stmtNum_pair =
      make_pair(ASSIGN_ENTITY, STMTNUM_ATTRREF);

  // varName attrRef
  pair<string, string> var_varName_pair =
      make_pair(VARIABLE_ENTITY, VARNAME_ATTRREF);
  pair<string, string> read_varName_pair =
      make_pair(READ_ENTITY, VARNAME_ATTRREF);
  pair<string, string> print_varName_pair =
      make_pair(PRINT_ENTITY, VARNAME_ATTRREF);

  // procName attrRef
  pair<string, string> proc_procName_pair =
      make_pair(PROCEDURE_ENTITY, PROCNAME_ATTRREF);
  pair<string, string> call_procName_pair =
      make_pair(CALL_ENTITY, PROCNAME_ATTRREF);

  // value attrRef
  pair<string, string> constant_value_pair =
      make_pair(CONSTANT_ENTITY, VALUE_ATTRREF);

  unordered_map<pair<string, string>, WithEvaluatorFunc> withEvaluatorFuncMap {
      {stmt_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluateStmtNum(pkbReader);
       }},
      {read_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluateReadStmtNum(pkbReader);
       }},
      {print_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluatePrintStmtNum(pkbReader);
       }},
      {call_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluateCallStmtNum(pkbReader);
       }},
      {while_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluateStmtNum(pkbReader);
       }},
      {if_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluateStmtNum(pkbReader);
       }},
      {assign_stmtNum_pair,
       [this](PKBReader& pkbReader) {
         return evaluateStmtNum(pkbReader);
       }},
      {read_varName_pair,
       [this](PKBReader& pkbReader) {
         return evaluateReadVarName(pkbReader);
       }},
      {var_varName_pair,
       [this](PKBReader& pkbReader) {
         return evaluateVarName(pkbReader);
       }},
      {read_varName_pair,
       [this](PKBReader& pkbReader) {
         return evaluateVarName(pkbReader);
       }},
      {print_varName_pair,
       [this](PKBReader& pkbReader) {
         return evaluatePrintVarName(pkbReader);
       }},
      {proc_procName_pair,
       [this](PKBReader& pkbReader) {
         return evaluateProcName(pkbReader);
       }},
      {call_procName_pair,
       [this](PKBReader& pkbReader) {
         return evaluateCallProcName(pkbReader);
       }},
      {constant_value_pair, 
       [this](PKBReader& pkbReader) {
         return evaluateConstantValue(pkbReader);
       }}};

 public:
  explicit WithClause(unique_ptr<AbstractArgument> synonym,
                      string synonymEntity, string& attrRef,
                      string& attrRefValue)
      : synonym(move(synonym)),
        synonymEntity(synonymEntity),
        attrRef(attrRef),
        attrRefValue(attrRefValue) {}
  IntermediateTable evaluate(Context& context, PKBReader& pkb) override;
};
