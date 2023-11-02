#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <utility>

#include "qps/clause/clauseDecorator/ClauseDecorator.h"

using std::function;

typedef function<vector<SynonymRes>(PKBReader& pkb)> NotDecoratorFunc;

class NotDecorator : public ClauseDecorator {
 protected:
  vector<SynonymRes> getAllStmts(PKBReader& pkb);
  vector<SynonymRes> getAllAssignStmts(PKBReader& pkb);
  vector<SynonymRes> getAllWhileStmts(PKBReader& pkb);
  vector<SynonymRes> getAllIfStmts(PKBReader& pkb);
  vector<SynonymRes> getAllPrintStmts(PKBReader& pkb);
  vector<SynonymRes> getAllReadStmts(PKBReader& pkb);
  vector<SynonymRes> getAllCallStmts(PKBReader& pkb);
  vector<SynonymRes> getAllConstants(PKBReader& pkb);
  vector<SynonymRes> getAllProcedures(PKBReader& pkb);
  vector<SynonymRes> getAllVariables(PKBReader& pkb);

  unordered_map<Entity, NotDecoratorFunc> notDecoratorFuncMap = {
      {ASSIGN_ENTITY,
        [this](PKBReader& pkb) { return getAllAssignStmts(pkb); }},
      {IF_ENTITY,
        [this](PKBReader& pkb) { return getAllIfStmts(pkb); }},
      {WHILE_ENTITY,
        [this](PKBReader& pkb) { return getAllWhileStmts(pkb); }},
      {STMT_ENTITY,
        [this](PKBReader& pkb) { return getAllStmts(pkb); }},
      {READ_ENTITY,
        [this](PKBReader& pkb) { return getAllReadStmts(pkb); }},
      {PRINT_ENTITY,
        [this](PKBReader& pkb) { return getAllPrintStmts(pkb); }},
      {CALL_ENTITY,
        [this](PKBReader& pkb) { return getAllCallStmts(pkb); }},
      {VARIABLE_ENTITY,
        [this](PKBReader& pkb) { return getAllVariables(pkb); }},
      {PROCEDURE_ENTITY,
        [this](PKBReader& pkb) { return getAllProcedures(pkb); }},
      {CONSTANT_ENTITY,
        [this](PKBReader& pkb) { return getAllConstants(pkb); }}};

 public:
  explicit NotDecorator(unique_ptr<Clause> wrapeeClause)
      : ClauseDecorator(std::move(wrapeeClause)) {}

  IntermediateTable evaluate(PKBReader& pkb) override;
  IntermediateTable generateMinuend(
      PKBReader& pkb, vector<unique_ptr<AbstractArgument>>& wrapeeClauseArgs);
  bool isEquals(const Clause& other) override;
};
