#pragma once

#include <set>
#include <string>

#include "pkb/interfaces/readers/IDesignEntitiesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"

class DesignEntitiesReader : public IDesignEntitiesReader {
 private:
  IEntityStorage& entity_storage_;
  IStmtStorage& stmt_storage_;

 protected:
  DesignEntitiesReader(IEntityStorage& entity_storage,
                       IStmtStorage& stmt_storage)
      : entity_storage_(entity_storage), stmt_storage_(stmt_storage) {}

 public:
  // return the names of all variables in the program
  std::set<std::string> getAllVariables() override;

  // return the values of all constants in the program
  std::set<std::string> getAllConstants() override;

  // return the names of all procedures in the program
  std::set<std::string> getAllProcedures() override;

  // return the statement numbers of specified statement type
  std::set<std::string> getStatement(StmtType statementType) override;

};
