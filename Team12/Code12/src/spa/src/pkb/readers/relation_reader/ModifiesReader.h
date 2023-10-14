#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "pkb/readers/relation_reader/stmt_or_proc_to_var_reader/ModifiesReaderImpl.h"

using std::unordered_set, std::string;

class ModifiesReader : public IModifiesReader {
 private:
  ModifiesReaderImpl modifies_reader_;

 protected:
  explicit ModifiesReader(IModifiesStorage& modifies_storage,
                          IStmtStorage& stmt_storage,
                          IEntityStorage& entity_storage)
      : modifies_reader_(modifies_storage, stmt_storage, entity_storage) {}

 public:
  std::vector<std::string> getStatementsModifying(
      const std::string& variableName, StmtType statementType) override;

  std::vector<std::string> getProceduresModifying(
      const std::string& variableName) override;

  std::vector<std::pair<std::string, std::string>> getVariablesModifiedBy(
      int statementNumber, StmtType statementType) override;

  std::vector<std::string> getModifiedVariablesForProc(
      const string& procName) override;

  bool isVariableModifiedBy(const std::string& variableName,
                            const std::string& statementNumber) override;

  bool isVariableModifiedByProc(const std::string& variableName,
                                const std::string& procName) override;

  std::vector<std::pair<std::string, std::string>> getAllModifiedVariables(
      StmtType statementType) override;

  std::vector<std::pair<std::string, std::string>>
  getAllModifiedVariablesByProcs() override;
};
