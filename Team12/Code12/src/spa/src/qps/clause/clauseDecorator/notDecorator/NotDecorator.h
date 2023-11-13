#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "qps/clause/clauseDecorator/ClauseDecorator.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/clause/utils/ClauseUtil.h"

using std::function;

typedef function<vector<std::reference_wrapper<SynonymRes>>(PKBReader& pkb)>
    NotDecoratorFunc;

class NotDecorator : public ClauseDecorator {
 private:
  IntermediateTable currentTable =
      IntermediateTableFactory::buildEmptyIntermediateTable();

 protected:
  unordered_map<Entity, NotDecoratorFunc> notDecoratorFuncMap = {
      {ASSIGN_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllAssignStmts(pkb); }},
      {IF_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllIfStmts(pkb); }},
      {WHILE_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllWhileStmts(pkb); }},
      {STMT_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllStmts(pkb); }},
      {READ_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllReadStmts(pkb); }},
      {PRINT_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllPrintStmts(pkb); }},
      {CALL_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllCallStmts(pkb); }},
      {VARIABLE_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllVariables(pkb); }},
      {PROCEDURE_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllProcedures(pkb); }},
      {CONSTANT_ENTITY,
       [this](PKBReader& pkb) { return ClauseUtil::getAllConstants(pkb); }}};

 public:
  explicit NotDecorator(unique_ptr<Clause> wrapeeClause)
      : ClauseDecorator(std::move(wrapeeClause)) {}

  IntermediateTable evaluate(PKBReader& pkb) override;
  IntermediateTable generateMinuend(
      PKBReader& pkb, vector<const AbstractArgument*>& wrapeeClauseArgs);
  void setCurrentTable(const IntermediateTable& currentTable);
  bool isEquals(const BaseClause& other) override;

  ClauseKey getKey() override;
};
