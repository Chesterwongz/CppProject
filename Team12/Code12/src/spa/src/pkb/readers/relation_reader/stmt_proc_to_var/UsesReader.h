#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/relation_storage/IUsesStorage.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/impl/UsesReaderImpl.h"

class UsesReader : public IUsesReader {
 private:
  UsesReaderImpl uses_reader_;

 protected:
  explicit UsesReader(IUsesStorage& uses_storage, IStmtStorage& stmt_storage,
                      IEntityStorage& entity_storage)
      : uses_reader_(uses_storage, stmt_storage, entity_storage) {}

 public:
  std::vector<std::string> getStatementsUsing(const std::string& variableName,
                                              StmtType statementType) override;

  std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(
      int statementNumber, StmtType statementType) override;

  bool isVariableUsedBy(const std::string& variableName,
                        const std::string& statementNumber) override;

  std::vector<std::pair<std::string, std::string>> getAllUsedVariables(
      StmtType statementType) override;

  std::unordered_set<std::string> getUsedVariablesForProc(
      const std::string& procName) override;
};
