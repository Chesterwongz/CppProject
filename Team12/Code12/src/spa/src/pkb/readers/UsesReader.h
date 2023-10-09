#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/interfaces/storage/relation_storage/IUsesStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"

class UsesReader : public virtual IUsesReader {
 private:
  IUsesStorage& uses_storage_;
  IStmtStorage& stmt_storage_;
  IEntityStorage& entity_storage_;

 protected:
  explicit UsesReader(IUsesStorage& modifies_storage,
                      IStmtStorage& stmt_storage,
                      IEntityStorage& entity_storage)
      : uses_storage_(modifies_storage),
        stmt_storage_(stmt_storage),
        entity_storage_(entity_storage) {}

 public:
  std::vector<std::string> getStatementsUsing(const std::string& variableName,
                                              StmtType statementType) override;

  std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(
      int statementNumber, StmtType statementType) override;

  bool isVariableUsedBy(const std::string& variableName,
                        const std::string& statementNumber) override;

  std::vector<std::pair<std::string, std::string>> getAllUsedVariables(
      StmtType statementType) override;
};
