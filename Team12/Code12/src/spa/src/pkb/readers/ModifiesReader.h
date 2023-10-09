#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/storage/relation_storage/stmt_or_proc_to_var/ModifiesStorage.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"

class ModifiesReader : public virtual IModifiesReader {
 private:
  IModifiesStorage& modifies_storage_;
  IStmtStorage& stmt_storage_;
  IEntityStorage& entity_storage_;

 protected:
  explicit ModifiesReader(IModifiesStorage& modifies_storage,
                          IStmtStorage& stmt_storage,
                          IEntityStorage& entity_storage)
      : modifies_storage_(modifies_storage),
        stmt_storage_(stmt_storage),
        entity_storage_(entity_storage) {}

 public:
  // return all s that satisfy Modifies(s, v) where v is variableName and s is
  // of same type as statementType
  std::vector<std::string> getStatementsModifying(
      const std::string& variableName, StmtType statementType) override;

  // return all pairs (s, v) that satisfy Modifies(s, v) where s is
  // statementNumber and also the correct statementType mentioned
  std::vector<std::pair<std::string, std::string>> getVariablesModifiedBy(
      int statementNumber, StmtType statementType) override;

  // check if Modifies(s, v) is true where s is statementNumber and v is the
  // variable name
  bool isVariableModifiedBy(const std::string& variableName,
                            const std::string& statementNumber) override;

  // return all pairs (s, v) that satisfy Modifies (s, v) where s is of a
  // particular type
  std::vector<std::pair<std::string, std::string>> getAllModifiedVariables(
      StmtType statementType) override;
};
