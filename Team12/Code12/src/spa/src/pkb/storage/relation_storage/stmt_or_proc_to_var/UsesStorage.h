#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include "StmtOrProcToVarRelationStorage.h"
#include "pkb/interfaces/storage/relation_storage/IUsesStorage.h"

class UsesStorage : public virtual IUsesStorage {
 private:
  StmtOrProcToVarRelationStorage storage_;

 public:
  void addUses(const std::string& variableName, int statementNumber) override;

  std::set<std::string> getVarsUsedByStmt(int statementNumber) override;

  std::set<int> getStmtsUsingVar(const std::string& variableName) override;

  // Return all variables that are being used in the program by some statement
  std::set<std::string> getAllVarUsedByStmt();

  // Return all statements that use a variable in the program
  std::set<int> getAllStmtUsingVar();
};
