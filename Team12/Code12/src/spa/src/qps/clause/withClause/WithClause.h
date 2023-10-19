#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "WithClauseUtils.h"
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
  Entity_AttrRef_Permutation permutation;

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

  unordered_map<Entity_AttrRef_Permutation, WithEvaluatorFunc>
      withEvaluatorFuncMap {
          {Entity_AttrRef_Permutation::STMT_STMTNUM,
           [this](PKBReader& pkbReader) { return evaluateStmtNum(pkbReader); }},
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
           [this](PKBReader& pkbReader) { return evaluateStmtNum(pkbReader); }},
          {Entity_AttrRef_Permutation::IF_STMTNUM,
           [this](PKBReader& pkbReader) { return evaluateStmtNum(pkbReader); }},
          {Entity_AttrRef_Permutation::ASSIGN_STMTNUM,
           [this](PKBReader& pkbReader) { return evaluateStmtNum(pkbReader); }},
          {Entity_AttrRef_Permutation::READ_VARNAME,
           [this](PKBReader& pkbReader) {
             return evaluateReadVarName(pkbReader);
           }},
          {Entity_AttrRef_Permutation::VAR_VARNAME,
           [this](PKBReader& pkbReader) { return evaluateVarName(pkbReader); }},
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
   // TODO(houten): change constructor based on kh pr
  explicit WithClause(unique_ptr<AbstractArgument> synonym,
                      Entity& synonymEntity, AttrRef& attrRef,
                      string& attrRefValue)
      : synonym(move(synonym)),
        synonymEntity(synonymEntity),
        attrRef(attrRef),
        attrRefValue(attrRefValue),
        permutation(getPermutation(synonymEntity, attrRef)) {}
  IntermediateTable evaluate(Context& context, PKBReader& pkb) override;
  bool isEquals(const Clause& other) override;
};
