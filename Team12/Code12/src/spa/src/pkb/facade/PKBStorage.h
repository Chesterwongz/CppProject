#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/PatternStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"
#include "pkb/storage/CallsStorage.h"

class PKBStorage {
 public:
  PKBStorage();

  // DesignEntitiesStorage methods
  virtual void setVariable(const std::string& variableName);
  virtual void setConstant(const std::string& constantValue);
  virtual void setProcedure(const std::string& procedureName,
                            int startStatement);

  std::set<std::string> getAllVariables();
  std::set<std::string> getAllConstants();
  std::set<std::string> getAllProcedures();

  // StatementStorage methods
  virtual void setStatement(int statementNumber, StmtType statementType);

  std::set<int> getStatementNumbersFromStatementType(StmtType statementType);

  StmtType getStatementTypeFromStatementNumber(int statementNumber);

  bool isStatementType(int statementNumber, StmtType statementType);

  // FollowsStorage methods
  void setFollows(int statementNumber, int followingStatement);

  int getImmediateFollows(int statementNumber);
  int getImmediateFollowedBy(int statementNumber);

  std::set<int> getAllFollows(int statementNumber);
  std::set<int> getAllFollowedBy(int statementNumber);

  // ParentStorage methods
  void setParent(int statementNumber, int childStatement);
  void setParentStar(int statementNumber, int childStatement);

  std::set<int> getImmediateChildren(int statementNumber);
  int getImmediateParent(int statementNumber);

  std::set<int> getAllChildren(int statementNumber);
  std::set<int> getAllParents(int statementNumber);

  // ModifiesStorage methods
  void setVariableModification(const std::string& variableName,
                               int statementNumber);

  void setVariableModification(const std::string& variableName,
                               const std::string& procName);

  std::set<std::string> getModifiedVariablesForStatement(int statementNumber);

  std::unordered_set<std::string> getModifiedVariablesForProc(
      const std::string& procName);

  std::set<int> getStatementNumbersForModifiedVariable(
      std::string variableName);

  // UsesStorage methods
  void setVariableUsage(const std::string& variableName, int statementNumber);

  void setVariableUsage(const std::string& variableName,
                        const std::string& procName);

  std::set<std::string> getUsedVariablesForStatement(int statementNumber);

  std::unordered_set<std::string> getUsedVariablesForProc(
      const std::string& procName);

  std::set<int> getStatementNumbersForUsedVariable(std::string variableName);

  // PatternStorage methods
  virtual void setAssignPattern(std::string variableName, std::string rpn,
                                int statementNumber);

  std::vector<std::string> getExactAssignPattern(std::string variableName,
                                                 std::string rpn,
                                                 bool isSynonym);
  std::vector<std::string> getPartialAssignPattern(std::string variableName,
                                                   std::string rpn,
                                                   bool isSynonym);

  // CallsStorage methods
  void setCalls(const std::string& callerProc, const std::string& calleeProc);
  void setCallsStar(const std::string& callerProc,
                    const std::string& calleeProc);
  const std::unordered_map<std::string, std::unordered_set<std::string>>&
  getCallsMap();
  std::unordered_set<std::string> getDirectProcsCalledBy(
      const std::string& callerProc);
  std::unordered_set<std::string> getAllProcsCalledBy(
      const std::string& callerProc);

 private:
  DesignEntitiesStorage designEntitiesStorage;
  FollowsStorage followsStorage;
  ModifiesStorage modifiesStorage;
  PatternStorage patternStorage;
  ParentStorage parentStorage;
  StatementStorage statementStorage;
  UsesStorage usesStorage;
  CallsStorage callsStorage;
};
