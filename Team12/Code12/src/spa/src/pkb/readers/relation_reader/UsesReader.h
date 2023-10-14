#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/relation_storage/IUsesStorage.h"
#include "pkb/readers/relation_reader/stmt_or_proc_to_var_reader/UsesReaderImpl.h"

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

  std::vector<std::string> getProceduresUsing(
      const std::string& variableName) override;

  std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(
      int statementNumber, StmtType statementType) override;

  std::vector<std::string> getUsedVariablesForProc(
      const std::string& procName) override;

  bool isVariableUsedBy(const std::string& variableName,
                        const std::string& statementNumber) override;

  bool isVariableUsedByProc(const std::string& variableName,
                            const std::string& procName) override;

  std::vector<std::pair<std::string, std::string>> getAllUsedVariables(
      StmtType statementType) override;

  std::vector<std::pair<std::string, std::string>> getAllUsedVariablesByProcs()
      override;
};
