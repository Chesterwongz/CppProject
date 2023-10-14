#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IUsesReader {
 public:
  virtual ~IUsesReader() = default;

  // return all s that satisfy Uses(s, v) where v is variableName and s is of
  // same type as statementType
  virtual std::vector<std::string> getStatementsUsing(
      const std::string& variableName, StmtType statementType) = 0;

  // return all p that satisfy Uses(p, v) where v is variableName
  virtual std::unordered_set<std::string> getProceduresUsing(
      const std::string& variableName) = 0;

  // return all pairs (s, v) that satisfy Uses(s, v) where s is statementNumber
  // and also the correct statementType mentioned
  virtual std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(
      int statementNumber, StmtType statementType) = 0;

  // return all variables used by specified procedure
  virtual std::unordered_set<std::string> getUsedVariablesForProc(
      const std::string& procName) = 0;

  // check if Used(s, v) is true where s is statementNumber and v is the
  // variable name
  virtual bool isVariableUsedBy(const std::string& variableName,
                                const std::string& statementNumber) = 0;

  // check if Used(p, v) is true where p is procName and v is the
  // variable name
  virtual bool isVariableUsedByProc(const std::string& variableName,
                                    const std::string& procName) = 0;

  // return all pairs (s, v) that satisfy Uses (s, v) where s is of a particular
  // type
  virtual std::vector<std::pair<std::string, std::string>> getAllUsedVariables(
      StmtType statementType) = 0;

  // return all pairs (p, v) that satisfy Uses (p, v)
  virtual std::vector<std::pair<std::string, std::string>>
  getAllUsedVariablesByProcs() = 0;
};
