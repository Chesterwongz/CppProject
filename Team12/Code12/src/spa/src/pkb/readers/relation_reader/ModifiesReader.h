#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/ModifiesReaderImpl.h"

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

  std::vector<std::pair<std::string, std::string>> getVariablesModifiedBy(
      int statementNumber, StmtType statementType) override;

  bool isVariableModifiedBy(const std::string& variableName,
                            const std::string& statementNumber) override;

  std::vector<std::pair<std::string, std::string>> getAllModifiedVariables(
      StmtType statementType) override;

  unordered_set<string> getModifiedVariablesForProc(
      const string& procName) override;
};
