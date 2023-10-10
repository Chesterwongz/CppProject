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
  vector<pair<string, string>> mockVariablesModifiedBy;
  vector<string> mockStatementsUsing;
  vector<pair<string, string>> mockVariablesUsedBy;
  vector<pair<string, string>> mockAllModifiedVariables;
  vector<pair<string, string>> mockAllUsedVariables;
  vector<string> mockExactAssignPattern;
  vector<string> mockPartialAssignPattern;
  bool mockIsFollowsStar{};
  bool mockIsParentStar{};
  bool mockIsFollows{};
  bool mockIsParent{};
  bool mockIsVariableModifiedBy{};
  bool mockIsVariableUsedBy{};
  vector<pair<string, string>> mockGetNextPairs;
  bool mockIsNext{};
  vector<string> mockgetPrevStmts;
  vector<string> mockgetNextStmts;
  vector<pair<string, string>> mockgetNextTPairs;
  bool mockisNextT{};
  vector<string> mockgetPrevTStmts;
  vector<string> mockgetNextTStmts;

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

  vector<pair<string, string>> getVariablesModifiedBy(
      int statementNumber, StmtType statementType) override {
    return mockVariablesModifiedBy;
  }

  vector<string> getStatementsUsing(const string& variableName,
                                    StmtType statementType) override {
    return mockStatementsUsing;
  }

  vector<pair<string, string>> getVariablesUsedBy(
      int statementNumber, StmtType statementType) override {
    return mockVariablesUsedBy;
  }

  vector<pair<string, string>> getAllModifiedVariables(
      StmtType statementType) override {
    return mockAllModifiedVariables;
  }

  vector<pair<string, string>> getAllUsedVariables(
      StmtType statementType) override {
    return mockAllUsedVariables;
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

  bool isVariableUsedBy(const string& variableName,
                        const string& statementNumber) override {
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
    return mockgetPrevStmts;
  };

  vector<string> getNextStmts(int firstStmtNumber,
                                  StmtType secondStmtType) override {
    return mockgetNextStmts;
  }

  vector<pair<string, string>> getNextTPairs(
      StmtType firstStmtType, StmtType secondStmtType) override {
    return mockgetNextTPairs;
  }

  bool isNextT(int firstStmtNumber, int secondStmtNumber) override {
    return mockisNextT;
  }

  vector<string> getPrevTStmts(int secondStmtNumber,
                                      StmtType firstStmtType) override {
    return mockgetPrevTStmts;
  }

  vector<string> getNextTStmts(int firstStmtNumber,
                                       StmtType secondStmtType) override {
    return mockgetNextTStmts;
  }
};
