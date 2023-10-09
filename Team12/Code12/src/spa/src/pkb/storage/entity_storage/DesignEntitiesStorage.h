#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"

class DesignEntitiesStorage : public virtual IEntityStorage {
 public:
  // Setter for variables
  void setVariable(const std::string& variableName) override;

  // Setter for constants
  void setConstant(const std::string& constantValue) override;

  // Setter for procedure names
  void setProcedure(const std::string& procedureName,
                    int startStatement) override;

  // Return the names of all variables in the program
  std::set<std::string> getAllVariables() override;

  // Return all constants in the program
  std::set<std::string> getAllConstants() override;

  // Return the names of all procedures in the program
  std::set<std::string> getAllProcedures() override;

  // Return the name of the procedure whose code begins on that particular
  // statement
  std::string getProcedureStartingOnStatement(int statementNumber) override;

  // Return the starting statement number of a particular procedure
  int getStartingStatementOfProcedure(
      const std::string& procedureName) override;

 private:
  std::set<std::string> variableData;

  std::set<std::string> constantData;

  // procedure name -> starting statement
  std::unordered_map<std::string, int> procedureData;
};
