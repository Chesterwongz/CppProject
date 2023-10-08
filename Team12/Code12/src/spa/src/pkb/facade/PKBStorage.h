#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/storage/CallsStorage.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/PatternStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

using std::set, std::string, std::vector, std::unordered_set, std::pair;

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

  unordered_set<string> getModifiedVariablesForProc(
      const std::string& procName);

  std::set<int> getStatementNumbersForModifiedVariable(
      std::string variableName);

  // UsesStorage methods
  void setVariableUsage(const std::string& variableName, int statementNumber);

  void setVariableUsage(const std::string& variableName,
                        const std::string& procName);

  std::set<std::string> getUsedVariablesForStatement(int statementNumber);

  unordered_set<string> getUsedVariablesForProc(const std::string& procName);

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
  void setCallsRelationship(const std::string& callerProc,
                            const std::string& calleeProc, int statementNumber);
  void setCallsStarRelationship(const std::string& callerProc,
                                const std::string& calleeProc,
                                int statementNumber);

  vector<pair<string, std::string>> getCallerProcs(const std::string& procName);
  vector<pair<string, std::string>> getCallerProcsStar(
      const std::string& procName);
  vector<pair<string, std::string>> getCalleeProcs(const std::string& procName);
  vector<pair<string, std::string>> getCalleeProcsStar(
      const std::string& procName);

  std::string getProcCalledOn(int statementNumber);
  vector<string> getProcStarCalledOn(int statementNumber);

  vector<pair<string, std::string>> getCallingProcedures();
  vector<pair<string, std::string>> getCalledProcedures();

  bool isCalling(const std::string& caller, const std::string& callee);
  bool isCallingStar(const std::string& caller, const std::string& callee);
  bool isCallingStmt(int statementNumber, const std::string& callee);
  bool isCallingStarStmt(int statementNumber, const std::string& callee);
  const unordered_map<string, vector<pair<int, std::string>>>&
  getCalleeProcsMap();

 private:
  CallsStorage callsStorage;
  DesignEntitiesStorage designEntitiesStorage;
  FollowsStorage followsStorage;
  ModifiesStorage modifiesStorage;
  PatternStorage patternStorage;
  ParentStorage parentStorage;
  StatementStorage statementStorage;
  UsesStorage usesStorage;
};
