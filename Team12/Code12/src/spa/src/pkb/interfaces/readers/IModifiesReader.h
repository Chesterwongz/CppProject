#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IModifiesReader {
 public:
  virtual ~IModifiesReader() = default;

  virtual std::vector<std::string> getVariablesModifiedBy(int stmtNum) = 0;

  virtual std::vector<std::string> getStatementsModifying(
      const std::string& varName, StmtType stmtType) = 0;

  virtual bool isVariableModifiedBy(int stmtNum,
                                    const std::string& varName) = 0;

  virtual std::vector<std::pair<std::string, std::string>> getModifiesStmtPairs(
      StmtType stmtType) = 0;

  virtual std::vector<std::string> getVarsModifiedByProc(
      const std::string& procName) = 0;

  virtual std::vector<std::string> getProcModifying(
      const std::string& varName) = 0;

  virtual bool isVariableModifiedByProc(const std::string& procName,
                                        const std::string& varName) = 0;

  virtual std::vector<std::pair<std::string, std::string>>
  getModifiesProcPairs() = 0;
};
