#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/utils/StringUtils.h"
#include "pkb/interfaces/storage/pattern_storage/IPatternStorage.h"
#include "qps/common/Keywords.h"

class PatternStorage : public virtual IPatternStorage {
 public:
  // Setter for assignment expressions in the program
  void setAssignPattern(const std::string& variableName, const std::string& rpn,
                        int statementNumber) override;

  // Return all statement numbers that contain the exact match
  std::vector<std::string> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) override;

  // Return all the statement numbers that contain a partial match
  std::vector<std::string> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) override;

  // Return all assignment statements
  std::vector<std::string> getAllStatements();

  // Return all assignment statements with variableName on the LHS
  std::vector<std::string> getAllStatementsWithVariable(
      const std::string& variableName);

 private:
  // variableName --> (RPN, stmtNum)
  std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>
      variablePatternStorage;

  // stmtNum --> (RPN, variableName)
  std::unordered_map<int, std::pair<std::string, std::string>>
      statementPatternStorage;
};
