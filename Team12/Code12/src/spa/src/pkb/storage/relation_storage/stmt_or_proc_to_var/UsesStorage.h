#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "StmtOrProcToVarRelationStorage.h"
#include "pkb/interfaces/storage/relation_storage/IUsesStorage.h"

using std::string;

class UsesStorage : public virtual IUsesStorage {
 private:
  StmtOrProcToVarRelationStorage storage_;

 public:
  void addUses(const std::string& variableName, int statementNumber) override;

  void addUses(const std::string& variableName,
               const std::string& procName) override;

  std::set<std::string> getVarsUsedByStmt(int statementNumber) override;

  std::unordered_set<std::string> getVarsUsedByProc(
      const string& procName) override;

  // Return all statements that use a specified variable in the program
  std::set<int> getStmtsUsingVar(const std::string& variableName) override;

  // Return all statements that use a specified variable in the program
  std::unordered_set<std::string> getProcsUsingVar(
      const std::string& variableName) override;

  // Return all variables that are being used in the program by some statement
  std::set<std::string> getAllVarUsedByStmt();

  // Return all statements that use any variable in the program
  std::set<int> getAllStmtUsingVar();
};
