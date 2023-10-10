#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "StmtOrProcToVarRelationStorage.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"

class ModifiesStorage : public IModifiesStorage {
 private:
  StmtOrProcToVarRelationStorage storage_;

 public:
  void addModifies(const std::string& varName, int stmtNum) override;

  void addModifies(const std::string& varName,
                   const std::string& procName) override;

  std::set<std::string> getVarsModifiedByStmt(int stmtNum) override;

  std::unordered_set<std::string> getVarsModifiedByProc(
      const std::string& procName) override;

  std::set<int> getStmtsModifyingVar(const std::string& varName) override;

  // Return all variables that are being modified in the program by some
  // statement.
  std::set<std::string> getAllVarsModifiedByStmt();

  // Return all statements that modify a variable in the program
  std::set<int> getAllStmtsModifyingVar();
};
