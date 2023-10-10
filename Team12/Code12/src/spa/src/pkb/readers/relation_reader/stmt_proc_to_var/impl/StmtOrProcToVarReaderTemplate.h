#pragma once

#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "pkb/storage/relation_storage/stmt_proc_to_var/ModifiesStorage.h"

using std::unordered_set, std::string;

class StmtOrProcToVarReaderTemplate {
 private:
  IStmtStorage& stmt_storage_;
  IEntityStorage& entity_storage_;

 protected:
  virtual std::set<std::string> getVarsRelatedToStmt(int stmtNum) = 0;
  virtual std::set<int> getStmtsRelatedToVar(const std::string& varName) = 0;

 public:
  explicit StmtOrProcToVarReaderTemplate(IStmtStorage& stmt_storage,
                                         IEntityStorage& entity_storage)
      : stmt_storage_(stmt_storage), entity_storage_(entity_storage) {}

  // return all s that satisfy Relation(s, v) where v is varName and s is
  // of same type as stmtType
  std::vector<std::string> getStmtsRelatedToVarByStmtType(
      const std::string& varName, StmtType stmtType);

  // return all pairs (s, v) that satisfy Relation(s, v) where s is
  // stmtNum and also the correct stmtType mentioned
  std::vector<std::pair<std::string, std::string>>
  getVarsRelatedToStmtByStmtType(int stmtNum, StmtType stmtType);

  // check if Relation(s, v) is true where s is stmtNumStr and v is the
  // variable name
  bool isVarRelatedToStmt(const std::string& varName,
                          const std::string& stmtNumStr);

  // return all pairs (s, v) that satisfy Relation (s, v) where s is of a
  // particular type
  std::vector<std::pair<std::string, std::string>> getAllRelationsByStmtType(
      StmtType statementType);

  // Proc-related functions
  virtual std::unordered_set<std::string> getVarsRelatedToProc(
      const string& proc) = 0;
};
