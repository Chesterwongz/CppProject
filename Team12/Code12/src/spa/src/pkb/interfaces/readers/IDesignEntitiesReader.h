#pragma once

#include <set>
#include <string>
#include "common/StmtTypes.h"

class IDesignEntitiesReader {
 public:
  virtual ~IDesignEntitiesReader() = default;

  // return the names of all variables in the program
  virtual std::set<std::string> getAllVariables() = 0;

  // return the values of all constants in the program
  virtual std::set<std::string> getAllConstants() = 0;

  // return the names of all procedures in the program
  virtual std::set<std::string> getAllProcedures() = 0;

  // return the names of all procedures in the program
  virtual std::set<std::string> getStatement(StmtType statementType) = 0;
};
