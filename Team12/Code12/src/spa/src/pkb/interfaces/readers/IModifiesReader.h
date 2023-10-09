#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IModifiesReader {
 public:
  virtual ~IModifiesReader() = default;

  // return all s that satisfy Modifies(s, v) where v is variableName and s is
  // of same type as statementType
  virtual std::vector<std::string> getStatementsModifying(
      const std::string& variableName, StmtType statementType) = 0;

  // return all pairs (s, v) that satisfy Modifies(s, v) where s is
  // statementNumber and also the correct statementType mentioned
  virtual std::vector<std::pair<std::string, std::string>>
  getVariablesModifiedBy(int statementNumber, StmtType statementType) = 0;

  // check if Modifies(s, v) is true where s is statementNumber and v is the
  // variable name
  virtual bool isVariableModifiedBy(const std::string& variableName,
                                    const std::string& statementNumber) = 0;

  // return all pairs (s, v) that satisfy Modifies (s, v) where s is of a
  // particular type
  virtual std::vector<std::pair<std::string, std::string>>
  getAllModifiedVariables(StmtType statementType) = 0;

  virtual std::unordered_set<std::string> getModifiedVariablesForProc(
      const std::string& procName) = 0;
};
