#pragma once

#include <vector>
#include <string>

#include "common/StmtTypes.h"

class IDesignEntitiesReader {
 public:
  virtual ~IDesignEntitiesReader() = default;

  // return the names of all variables in the program
  virtual std::vector<std::string> getAllVariables() = 0;

  // return the values of all constants in the program
  virtual std::vector<std::string> getAllConstants() = 0;

  // return the names of all procedures in the program
  virtual std::vector<std::string> getAllProcedures() = 0;

  // return all the stmts of given type in the program
  virtual std::vector<std::string> getAllStmtsOf(StmtType statementType) = 0;
};
