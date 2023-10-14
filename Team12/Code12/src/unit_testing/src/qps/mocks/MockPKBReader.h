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
#include "pkb/facade/PKBStore.h"
#include "pkb/storage/CallsStore.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesStore.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/ParentStore.h"
#include "pkb/storage/RelationTStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesPStore.h"
#include "pkb/storage/UsesStore.h"

using std::vector, std::set, std::string, std::pair;

class MockPKBReader : public PKBReader {
 public:
  set<string> mockAllVariables;
  set<string> mockAllConstants;
  set<string> mockAllProcedures;
  set<string> mockStatements;
  vector<string> mockFollowing;
  vector<string> mockFollowed;
  vector<pair<string, string>> mockFollowsPairs;
  vector<string> mockFollowsStar;
  vector<string> mockFollowedStar;
  vector<pair<string, string>> mockFollowedPairs;
  vector<pair<string, string>> mockFollowsStarPairs;
  vector<string> mockImmediateChildrenOf;
  vector<string> mockImmediateParentOf;
  vector<pair<string, string>> mockParentChildPairs;
  vector<string> mockChildrenStar;
  vector<string> mockParentStarOf;
  vector<pair<string, string>> mockParentChildStarPairs;
  vector<string> mockStatementsModifying;
  vector<pair<string, string>> mockVariablesModifiedBy;
  vector<string> mockStatementsUsing;
  vector<pair<string, string>> mockVariablesUsedBy;
  vector<pair<string, string>> mockAllModifiedVariables;
  vector<pair<string, string>> mockAllUsedVariables;
  vector<pair<string, string>> mockExactAssignPattern;
  vector<pair<string, string>> mockPartialAssignPattern;
  bool mockIsFollowsStar{};
  bool mockIsParentStar{};
  bool mockIsFollows{};
  bool mockIsParent{};
  bool mockIsVariableModifiedBy{};
  bool mockIsVariableUsedBy{};
  vector<pair<string, string>> mockGetNextPairs;
  bool mockIsNext{};
  vector<string> mockGetPrevStmts;
  vector<string> mockGetNextStmts;
  vector<pair<string, string>> mockGetNextTPairs;
  bool mockIsNextT{};
  vector<string> mockGetPrevTStmts;
  vector<string> mockGetNextTStmts;

  explicit MockPKBReader(PKBStorage& storage, PKBStore& store)
      : PKBReader(storage, store) {}

  set<string> getAllVariables() override { return mockAllVariables; }

  set<string> getAllConstants() override { return mockAllConstants; }

  set<string> getAllProcedures() override { return mockAllProcedures; }

  set<string> getStatement(StmtType statementType) override {
    return mockStatements;
  }

  std::vector<std::string> getFollowing(int statementNumber,
                                        StmtType statementType) override {
    return mockFollowing;
  }

  std::vector<std::string> getFollowed(int statementNumber,
                                       StmtType statementType) override {
    return mockFollowed;
  }

  vector<pair<string, string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsPairs;
  }

  std::vector<std::string> getFollowsStar(int statementNumber,
                                          StmtType statementType) override {
    return mockFollowsStar;
  }

  std::vector<std::string> getFollowedStar(int statementNumber,
                                           StmtType statementType) override {
    return mockFollowedStar;
  }

  vector<pair<string, string>> getFollowsStarPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsStarPairs;
  }

  std::vector<std::string> getImmediateChildrenOf(
      int statementNumber, StmtType statementType) override {
    return mockImmediateChildrenOf;
  }

  std::vector<std::string> getImmediateParentOf(
      int statementNumber, StmtType statementType) override {
    return mockImmediateParentOf;
  }

  vector<pair<string, string>> getParentChildPairs(
      StmtType parentType, StmtType childType) override {
    return mockParentChildPairs;
  }

  std::vector<std::string> getChildrenStarOf(int statementNumber,
                                             StmtType statementType) override {
    return mockChildrenStar;
  }

  std::vector<std::string> getParentStarOf(int statementNumber,
                                           StmtType statementType) override {
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

  vector<pair<string, string>> getVariablesModifiedBy(
      int statementNumber, StmtType statementType) override {
    return mockVariablesModifiedBy;
  }

  vector<string> getStatementsUsing(const string& variableName,
                                    StmtType statementType) override {
    return mockStatementsUsing;
  }

  std::vector<std::string> getVariablesUsedBy(int statementNumber,
                                              StmtType statementType) override {
    return mockVariablesUsedBy;
  }

  vector<pair<string, string>> getAllModifiedVariables(
      StmtType statementType) override {
    return mockAllModifiedVariables;
  }

  vector<pair<string, string>> getUsesPairs(
      StmtType statementType) override {
    return mockAllUsedVariables;
  }

  vector<pair<string, string>> getExactAssignPattern(
      const string& variableName, const string& rpn) override {
    return mockExactAssignPattern;
  }

  vector<pair<string, string>> getPartialAssignPattern(
      const string& variableName, const string& rpn) override {
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

  bool isVariableUsedBy(int stmt, const string& varName) override {
    return mockIsVariableUsedBy;
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
