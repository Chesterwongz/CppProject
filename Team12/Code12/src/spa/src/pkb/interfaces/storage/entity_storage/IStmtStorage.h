#pragma once

#include <set>
#include <string>
#include "common/StmtTypes.h"

class IStmtStorage {
 public:
  virtual ~IStmtStorage() = default;

  // Setter for each statement type
  virtual void setStatement(int statementNumber, StmtType statementType) = 0;

  // Return all statements of a particular type
  virtual std::set<int> getStatementNumbersFromStatementType(
      StmtType statementType) = 0;

  // Return the type of a particular statement
  virtual StmtType getStatementTypeFromStatementNumber(int statementNumber) = 0;

  virtual bool isStatementType(int statementNumber, StmtType statementType) = 0;
};
