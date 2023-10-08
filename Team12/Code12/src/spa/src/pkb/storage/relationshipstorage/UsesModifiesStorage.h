#pragma once

#include <string>
#include <set>
#include "UsesStorage.h"
#include "ModifiesStorage.h"
#include "pkb/interfaces/storage/IUsesStorage.h"
#include "pkb/interfaces/storage/IModifiesStorage.h"

// TODO (Chester): Split this up, and have UsesStorage and ModifiesStorage
//  both have the same datastructure.
class UsesModifiesStorage : public virtual IUsesStorage,
                            public virtual IModifiesStorage {
 private:
  UsesStorage uses_storage_;
  ModifiesStorage modifies_storage_;

 public:
  // ModifiesStorage methods
  void setVariableModification(const std::string& variableName,
                               int statementNumber) override;

  std::set<std::string> getModifiedVariablesForStatement(
      int statementNumber) override;

  std::set<int> getStatementNumbersForModifiedVariable(
      const std::string& variableName) override;

  // UsesStorage methods
  void setVariableUsage(const std::string& variableName,
                        int statementNumber) override;

  std::set<std::string> getUsedVariablesForStatement(
      int statementNumber) override;

  std::set<int> getStatementNumbersForUsedVariable(
      const std::string& variableName) override;
};
