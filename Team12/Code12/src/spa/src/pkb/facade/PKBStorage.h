#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
  virtual void setVariable(const string& varName);
  virtual void setConstant(const string& constantValue);
  virtual void setProcedure(const string& procedureName, int startStatement);

  set<string> getAllVariables();
  set<string> getAllConstants();
  set<string> getAllProcedures();

  // StatementStorage methods
  virtual void setStatement(int stmtNum, StmtType statementType);

  set<int> getStatementNumbersFromStatementType(StmtType statementType);

  StmtType getStatementTypeFromStatementNumber(int stmtNum);

  bool isStatementType(int stmtNum, StmtType statementType);

  // FollowsStorage methods
  void setFollows(int stmtNum, int followingStatement);

  int getImmediateFollows(int stmtNum);
  int getImmediateFollowedBy(int stmtNum);

  set<int> getAllFollows(int stmtNum);
  set<int> getAllFollowedBy(int stmtNum);

  // ParentStorage methods
  void setParent(int stmtNum, int childStatement);
  void setParentStar(int stmtNum, int childStatement);

  set<int> getImmediateChildren(int stmtNum);
  int getImmediateParent(int stmtNum);

  set<int> getAllChildren(int stmtNum);
  set<int> getAllParents(int stmtNum);

  // ModifiesStorage methods
  void setVariableModification(const string& varName, int stmtNum);

  void setVariableModification(const string& varName, const string& procName);

  set<string> getModifiedVariablesForStatement(int stmtNum);

  unordered_set<string> getModifiedVariablesForProc(const string& procName);

  set<int> getStatementNumbersForModifiedVariable(string varName);

  // UsesStorage methods
  void setVariableUsage(const string& varName, int stmtNum);

  void setVariableUsage(const string& varName, const string& procName);

  set<string> getUsedVariablesForStatement(int stmtNum);

  unordered_set<string> getUsedVariablesForProc(const string& procName);

  set<int> getStatementNumbersForUsedVariable(string varName);

  // PatternStorage methods
  virtual void setAssignPattern(string varName, string rpn, int stmtNum);

  vector<string> getExactAssignPattern(string varName, string rpn,
                                       bool isSynonym);
  vector<string> getPartialAssignPattern(string varName, string rpn,
                                         bool isSynonym);

  // CallsStorage methods
  void setCallsRelationship(const string& callerProc, const string& calleeProc,
                            int stmtNum);
  void setCallsStarRelationship(const string& callerProc,
                                const string& calleeProc, int stmtNum);

  vector<pair<string, string>> getCalledBy(const string& procName);
  vector<pair<string, string>> getCalledStarBy(const string& procName);
  vector<pair<string, string>> getProcsThatCall(const string& procName);
  vector<pair<string, string>> getProcsThatCallStar(const string& procName);

  string getProcCalledOn(int stmtNum);
  vector<string> getProcStarCalledOn(int stmtNum);

  vector<pair<string, string>> getCallingProcedures();
  vector<pair<string, string>> getCalledProcedures();

  bool isCalling(const string& caller, const string& callee);
  bool isCallingStar(const string& caller, const string& callee);
  bool isCallingStmt(int stmtNum, const string& callee);
  bool isCallingStarStmt(int stmtNum, const string& callee);
  const unordered_map<string, vector<pair<int, string>>>& getCallsMap();

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
