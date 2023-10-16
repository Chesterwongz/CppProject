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

  virtual std::vector<std::pair<std::string, std::string>> getModifiesPairs(
      StmtType stmtType) = 0;

  virtual std::unordered_set<std::string> getModifiedVariablesForProc(
      const std::string& procName) = 0;
};
