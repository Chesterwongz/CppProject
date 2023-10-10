#pragma once

#include <set>
#include <string>
#include <unordered_map>

#include "common/Constants.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"

class DesignEntitiesStorage : public IEntityStorage {
 public:
  // Setter for variables
  void setVariable(const std::string& variableName) override;

  // Setter for constants
  void setConstant(const std::string& constantValue) override;

  // Setter for procedure names
  void setProcForStmt(const std::string& procedureName, int stmt) override;

  // Return the names of all variables in the program
  std::set<std::string> getAllVariables() override;

  // Return all constants in the program
  std::set<std::string> getAllConstants() override;

  // Return the names of all procedures in the program
  std::set<std::string> getAllProcedures() override;

  std::string getProcFromStmt(int stmtNum) override;

 private:
  std::set<std::string> variableData;

  std::set<std::string> constantData;

  std::set<std::string> procedureData;

  std::unordered_map<int, std::string> stmtToProcMap;
};
