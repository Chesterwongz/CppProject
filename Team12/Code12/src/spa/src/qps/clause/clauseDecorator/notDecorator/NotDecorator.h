#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "qps/clause/clauseDecorator/ClauseDecorator.h"

using std::function;

typedef function<vector<std::reference_wrapper<SynonymRes>>(PKBReader& pkb)>
    NotDecoratorFunc;

class NotDecorator : public ClauseDecorator {
 private:
  static vector<std::reference_wrapper<SynonymRes>> getStmtSynonyms(
      vector<string>& stmts);

 protected:
  vector<std::reference_wrapper<SynonymRes>> getAllStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllAssignStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllWhileStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllIfStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllPrintStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllReadStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllCallStmts(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllConstants(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllProcedures(PKBReader& pkb);
  vector<std::reference_wrapper<SynonymRes>> getAllVariables(PKBReader& pkb);

  unordered_map<Entity, NotDecoratorFunc> notDecoratorFuncMap = {
      {ASSIGN_ENTITY,
       [this](PKBReader& pkb) { return getAllAssignStmts(pkb); }},
      {IF_ENTITY, [this](PKBReader& pkb) { return getAllIfStmts(pkb); }},
      {WHILE_ENTITY, [this](PKBReader& pkb) { return getAllWhileStmts(pkb); }},
      {STMT_ENTITY, [this](PKBReader& pkb) { return getAllStmts(pkb); }},
      {READ_ENTITY, [this](PKBReader& pkb) { return getAllReadStmts(pkb); }},
      {PRINT_ENTITY, [this](PKBReader& pkb) { return getAllPrintStmts(pkb); }},
      {CALL_ENTITY, [this](PKBReader& pkb) { return getAllCallStmts(pkb); }},
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
      PKBReader& pkb, vector<const AbstractArgument*>& wrapeeClauseArgs);
  bool isEquals(const IClause& other) override;
};
