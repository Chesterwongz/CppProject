#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/interfaces/storage/entitystorage/IStmtStorage.h"

class StmtStorage : public virtual IStmtStorage {
 private:
  std::unordered_map<StmtType, std::set<int>> statements;

 public:
  // Setter for each statement type
  void setStatement(int statementNumber, StmtType statementType) override;

  // Return all statement numbers of the program
  std::set<int> getAllStatements();

  // Return all statements of a particular type
  std::set<int> getStatementNumbersFromStatementType(
      StmtType statementType) override;

  // Return the type of a particular statement
  StmtType getStatementTypeFromStatementNumber(int statementNumber) override;

  bool isStatementType(int statementNumber, StmtType statementType) override;
};
