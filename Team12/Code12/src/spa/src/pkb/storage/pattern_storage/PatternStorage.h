#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
  // Setter for variables present in while conditions in the program
  void setWhilePattern(int statementNumber,
                       const std::string& variableName) override;
  // Setter for variables present in if conditons in the program
  void setIfPattern(int statementNumber,
                    const std::string& variableName) override;

  // Return all pairs (stmtNum, variableName) that contain the exact match
  std::vector<std::pair<std::string, std::string>> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn) override;

  // Return all pairs (stmtNum, variableName) that contain a partial match
  std::vector<std::pair<std::string, std::string>> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn) override;

  // Return all assignment statements
  std::vector<std::pair<std::string, std::string>> getAllAssignStatements();

  // Return all assignment statements with variableName on the LHS
  std::vector<std::pair<std::string, std::string>>
  getAllAssignStatementsWithVariable(const std::string& variableName);

  std::vector<std::pair<std::string, std::string>> getAssignPattern(
      const std::string& variableName, const std::string& rpn, bool isExact);

  std::vector<std::pair<std::string, std::string>> getConditionPattern(
      const std::unordered_map<int, std::unordered_set<std::string>>& storage,
      const std::string& variableName);

  // Return all pairs (stmtNum, variableName) where variableName is a variable
  // present in the condition of a while statement at stmtNum
  std::vector<std::pair<std::string, std::string>> getWhilePattern(
      const std::string& variableName) override;

  // Return all pairs (stmtNum, variableName) where variableName is a variable
  // present in the condition of an if statement at stmtNum
  std::vector<std::pair<std::string, std::string>> getIfPattern(
      const std::string& variableName) override;

 private:
  // variableName --> (RPN, stmtNum)
  std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>
      variablePatternStorage;

  // stmtNum --> (RPN, variableName)
  std::unordered_map<int, std::pair<std::string, std::string>>
      statementPatternStorage;

  // stmtNum --> variables
  std::unordered_map<int, std::unordered_set<std::string>> whilePatternStorage;

  // stmtNum --> variables
  std::unordered_map<int, std::unordered_set<std::string>> ifPatternStorage;
};
