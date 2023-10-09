#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/readers/template/ModifiesReaderImpl.h"

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
};
