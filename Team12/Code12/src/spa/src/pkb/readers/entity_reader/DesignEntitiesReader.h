#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "common/utils/StringUtils.h"
#include "pkb/interfaces/readers/IDesignEntitiesReader.h"
#include "pkb/storage/EntityStore.h"
#include "pkb/storage/StmtStore.h"

class DesignEntitiesReader : public IDesignEntitiesReader {
 private:
  EntityStore& entityStore;
  StmtStore& stmtStore;

 protected:
  DesignEntitiesReader(EntityStore& entityStore, StmtStore& stmtStore)
      : entityStore(entityStore), stmtStore(stmtStore) {}

 public:
  // return the names of all variables in the program
  std::vector<std::string> getAllVariables() override;

  // return the values of all constants in the program
  std::vector<std::string> getAllConstants() override;

  // return the names of all procedures in the program
  std::vector<std::string> getAllProcedures() override;

  // return the statement numbers of specified statement type
  std::vector<std::string> getAllStmtsOf(StmtType statementType) override;
};
