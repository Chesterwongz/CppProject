#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IModifiesReader {
 public:
  virtual std::vector<std::string> getStatementsModifying(
      const std::string& variableName, StmtType statementType) = 0;
  virtual std::vector<std::pair<std::string, std::string>>
  getVariablesModifiedBy(int statementNumber, StmtType statementType) = 0;
  virtual bool isVariableModifiedBy(const std::string& variableName,
                                    const std::string& statementNumber) = 0;
};
