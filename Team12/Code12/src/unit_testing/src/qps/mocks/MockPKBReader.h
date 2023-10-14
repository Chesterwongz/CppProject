#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"

using std::vector, std::set, std::string, std::pair;

class MockPKBReader : public PKBReader {
 public:
  set<string> mockAllVariables;
  set<string> mockAllConstants;
  set<string> mockAllProcedures;
  set<string> mockStatements;
  string mockFollowing;
  string mockFollowed;
  vector<pair<string, string>> mockFollowsPairs;
  vector<pair<string, string>> mockFollowsStar;
  vector<pair<string, string>> mockFollowedStar;
  vector<pair<string, string>> mockFollowedPairs;
  vector<pair<string, string>> mockFollowsStarPairs;
  vector<pair<string, string>> mockImmediateChildrenOf;
  pair<string, string> mockImmediateParentOf;
  vector<pair<string, string>> mockParentChildPairs;
  vector<pair<string, string>> mockChildrenStar;
  vector<pair<string, string>> mockParentStarOf;
  vector<pair<string, string>> mockParentChildStarPairs;
  vector<string> mockStatementsModifying;
  std::unordered_set<std::string> mockProceduresModifying;
  vector<pair<string, string>> mockVariablesModifiedBy;
  std::unordered_set<std::string> mockModifiedVariablesForProc;
  vector<string> mockStatementsUsing;
  unordered_set<string> mockProceduresUsing;
  vector<pair<string, string>> mockVariablesUsedBy;
  std::unordered_set<std::string> mockUsedVariablesForProc;
  vector<pair<string, string>> mockAllModifiedVariables;
  vector<pair<string, string>> mockAllModifiedVariablesByProcs;
  vector<pair<string, string>> mockAllUsedVariables;
  vector<pair<string, string>> mockAllUsedVariablesByProcs;
  vector<string> mockExactAssignPattern;
  vector<string> mockPartialAssignPattern;
  bool mockIsFollowsStar{};
  bool mockIsParentStar{};
  bool mockIsFollows{};
  bool mockIsParent{};
  bool mockIsVariableModifiedBy{};
  bool mockIsVariableModifiedByProc{};
  bool mockIsVariableUsedBy{};
  bool mockIsVariableUsedByProc{};
  vector<pair<string, string>> mockGetNextPairs;
  bool mockIsNext{};
  vector<string> mockGetPrevStmts;
  vector<string> mockGetNextStmts;
  vector<pair<string, string>> mockGetNextTPairs;
  bool mockIsNextT{};
  vector<string> mockGetPrevTStmts;
  vector<string> mockGetNextTStmts;

  explicit MockPKBReader(PKBStorage& storage) : PKBReader(storage) {}

  set<string> getAllVariables() override { return mockAllVariables; }

  set<string> getAllConstants() override { return mockAllConstants; }

  set<string> getAllProcedures() override { return mockAllProcedures; }

  set<string> getStatement(StmtType statementType) override {
    return mockStatements;
  }

  string getFollowing(int statementNumber, StmtType statementType) override {
    return mockFollowing;
  }

  string getFollowed(int statementNumber, StmtType statementType) override {
    return mockFollowed;
  }

  vector<pair<string, string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsPairs;
  }

  vector<pair<string, string>> getFollowsStar(int statementNumber,
                                              StmtType statementType) override {
    return mockFollowsStar;
  }

  vector<pair<string, string>> getFollowedStar(
      int statementNumber, StmtType statementType) override {
    return mockFollowedStar;
  }

  vector<pair<string, string>> getFollowsStarPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsStarPairs;
  }

  vector<pair<string, string>> getImmediateChildrenOf(
      int statementNumber, StmtType statementType) override {
    return mockImmediateChildrenOf;
  }

  pair<string, string> getImmediateParentOf(int statementNumber,
                                            StmtType statementType) override {
    return mockImmediateParentOf;
  }

  vector<pair<string, string>> getParentChildPairs(
      StmtType parentType, StmtType childType) override {
    return mockParentChildPairs;
  }

  vector<pair<string, string>> getChildrenStarOf(
      int statementNumber, StmtType statementType) override {
    return mockChildrenStar;
  }

  vector<pair<string, string>> getParentStarOf(
      int statementNumber, StmtType statementType) override {
    return mockParentStarOf;
  }

  vector<pair<string, string>> getParentChildStarPairs(
      StmtType parentType, StmtType childType) override {
    return mockParentChildStarPairs;
  }

  vector<string> getStatementsModifying(const string& variableName,
                                        StmtType statementType) override {
    return mockStatementsModifying;
  }

  std::unordered_set<std::string> getProceduresModifying(
      const std::string& variableName) override {
    return mockProceduresModifying;
  }

  vector<pair<string, string>> getVariablesModifiedBy(
      int statementNumber, StmtType statementType) override {
    return mockVariablesModifiedBy;
  }

  // return all variables modified by specified procedure
  std::unordered_set<std::string> getModifiedVariablesForProc(
      const std::string& procName) override {
    return mockModifiedVariablesForProc;
  }

  vector<string> getStatementsUsing(const string& variableName,
                                    StmtType statementType) override {
    return mockStatementsUsing;
  }

  std::unordered_set<std::string> getProceduresUsing(
      const std::string& variableName) override {
    return mockProceduresUsing;
  }

  vector<pair<string, string>> getVariablesUsedBy(
      int statementNumber, StmtType statementType) override {
    return mockVariablesUsedBy;
  }

  std::unordered_set<std::string> getUsedVariablesForProc(
      const std::string& procName) override {
    return mockUsedVariablesForProc;
  }

  vector<pair<string, string>> getAllModifiedVariables(
      StmtType statementType) override {
    return mockAllModifiedVariables;
  }

  vector<pair<string, string>> getAllModifiedVariablesByProcs() override {
    return mockAllModifiedVariablesByProcs;
  }

  vector<pair<string, string>> getAllUsedVariables(
      StmtType statementType) override {
    return mockAllUsedVariables;
  }

  std::vector<std::pair<std::string, std::string>>
  getAllUsedVariablesByProcs() override {
    return mockAllUsedVariablesByProcs;
  }

  vector<string> getExactAssignPattern(const string& variableName,
                                       const string& rpn,
                                       bool isSynonym) override {
    return mockExactAssignPattern;
  }

  vector<string> getPartialAssignPattern(const string& variableName,
                                         const string& rpn,
                                         bool isSynonym) override {
    return mockPartialAssignPattern;
  }

  void resetMockExactAssignPatternStmts() { this->mockExactAssignPattern = {}; }

  void resetMockPartialAssignPatternStmts() {
    this->mockPartialAssignPattern = {};
  }

  bool isFollows(int statementNumber, int followingStatement) override {
    return mockIsFollows;
  }

  bool isFollowsStar(int statementNumber, int followingStatement) override {
    return mockIsFollowsStar;
  }

  bool isParent(int statementNumber, int followingStatement) override {
    return mockIsParent;
  }

  bool isParentStar(int statementNumber, int followingStatement) override {
    return mockIsParentStar;
  }

  bool isVariableModifiedBy(const string& variableName,
                            const string& statementNumber) override {
    return mockIsVariableModifiedBy;
  }

  bool isVariableModifiedByProc(const std::string& variableName,
                                        const std::string& procName) override {
   return mockIsVariableModifiedByProc;
  }

  bool isVariableUsedBy(const string& variableName,
                        const string& statementNumber) override {
    return mockIsVariableUsedBy;
  }

  bool isVariableUsedByProc(const std::string& variableName,
                            const std::string& procName) override {
    return mockIsVariableUsedByProc;
  }

  vector<pair<string, string>> getNextPairs(StmtType firstStmtType,
                                            StmtType secondStmtType) override {
    return mockGetNextPairs;
  }

  bool isNext(int firstStmtNumber, int secondStmtNumber) override {
    return mockIsNext;
  }

  vector<string> getPrevStmts(int secondStmtNumber,
                              StmtType firstStmtType) override {
    return mockGetPrevStmts;
  };

  vector<string> getNextStmts(int firstStmtNumber,
                              StmtType secondStmtType) override {
    return mockGetNextStmts;
  }

  vector<pair<string, string>> getNextTPairs(StmtType firstStmtType,
                                             StmtType secondStmtType) override {
    return mockGetNextTPairs;
  }

  bool isNextT(int firstStmtNumber, int secondStmtNumber) override {
    return mockIsNextT;
  }

  vector<string> getPrevTStmts(int secondStmtNumber,
                               StmtType firstStmtType) override {
    return mockGetPrevTStmts;
  }

  vector<string> getNextTStmts(int firstStmtNumber,
                               StmtType secondStmtType) override {
    return mockGetNextTStmts;
  }
};
