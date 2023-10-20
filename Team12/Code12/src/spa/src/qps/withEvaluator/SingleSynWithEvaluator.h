#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/withClause/WithClauseUtils.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/withEvaluator/IWithEvaluator.h"

using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
    std::function, std::make_unique;

typedef function<IntermediateTable(PKBReader& pkbReader)> WithEvaluatorFunc;

class SingleSynWithEvaluator : public IWithEvaluator {
 protected:
  unique_ptr<SynonymArg> synonymArg;
  unique_ptr<AbstractArgument> valueArg;

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
      withEvaluatorFuncMapSingleSyn {
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
  explicit SingleSynWithEvaluator(unique_ptr<SynonymArg> firstArg,
                                  unique_ptr<AbstractArgument> secondArg)
      : synonymArg(move(firstArg)), valueArg(move(secondArg)) {};

  IntermediateTable evaluate(PKBReader& pkbReader) override;
};
