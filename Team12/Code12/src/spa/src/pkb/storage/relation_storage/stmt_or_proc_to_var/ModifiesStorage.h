#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "StmtOrProcToVarRelationStorage.h"

class ModifiesStorage : public virtual IModifiesStorage {
 private:
  StmtOrProcToVarRelationStorage storage_;

 public:
  void addModifies(const std::string& varName, int stmtNum) override;

  std::set<std::string> getVarsModifiedByStmt(int stmtNum) override;

  std::set<int> getStmtsModifyingVar(const std::string& varName) override;

  // Return all variables that are being modified in the program by some
  // statement.
  std::set<std::string> getAllVarsModifiedByStmt();

  // Return all statements that modify a variable in the program
  std::set<int> getAllStmtsModifyingVar();
};
