#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/cfg/CFG.h"
#include "pkb/facade/PKBWriter.h"

using std::string, std::unordered_set, std::unordered_map, std::set, std::pair;

class MockPKBWriter : public PKBWriter {
 private:
  unordered_set<string> variableStorage;
  unordered_set<string> constantStorage;
  unordered_map<int, string> stmtToProcStorage;
  unordered_map<StmtType, unordered_set<int>> statementStorage;
  unordered_map<int, set<int>> followsStorage;
  unordered_map<int, set<int>> parentStorage;
  unordered_map<int, set<int>> parentStarStorage;
  unordered_map<string, unordered_set<int>> modifiesStorage;
  unordered_map<string, unordered_set<string>>
      modifiesProcStorage;  // var to proc
  unordered_map<string, unordered_set<int>> usesStorage;
  unordered_map<string, unordered_set<string>> usesProcStorage;  // var to proc
  unordered_map<int, std::pair<string, string>> assignPatternStorage;
  unordered_map<int, unordered_set<string>> whilePatternStorage;
  unordered_map<int, unordered_set<string>> ifPatternStorage;
  unordered_map<string, unordered_set<string>> callsStorage;
  unordered_map<string, unique_ptr<CFG>> cfgStorage;
  IntToIntSetMap nextStorage;

 public:
  explicit MockPKBWriter(PKBStorage &storage) : PKBWriter(storage) {}
  ~MockPKBWriter() override = default;

  void setFollowsRelationship(int stmtNum, int followingStmt) override {
    followsStorage[stmtNum].insert(followingStmt);
  }

  void setParentRelationship(int stmtNum, int childStmt) override {
    parentStorage[stmtNum].insert(childStmt);
  }

  void setParentStarRelationship(int stmtNum, int childStmt) override {
    parentStarStorage[stmtNum].insert(childStmt);
  }

  void setModifiesRelationship(const string &varName, int stmtNum) override {
    modifiesStorage[varName].insert(stmtNum);
  }

  void setModifiesRelationship(const string &varName,
                               const string &procName) override {
    modifiesProcStorage[varName].insert(procName);
  }

  void setUsesRelationship(const string &varName, int stmtNum) override {
    usesStorage[varName].insert(stmtNum);
  }

  void setUsesRelationship(const string &varName,
                           const string &procName) override {
    usesProcStorage[varName].insert(procName);
  }

  void setVariable(const string &varName) override {
    variableStorage.insert(varName);
  }

  void setConstant(const string &constantValue) override {
    constantStorage.insert(constantValue);
  }

  void setProcForStmt(const string &procName, int stmtNum) override {
    stmtToProcStorage[stmtNum] = procName;
  }

  void setStatement(int stmtNum, StmtType statementType) override {
    statementStorage[statementType].insert(stmtNum);
  }

  void setAssignPattern(const string &varName, const string &expr,
                        int lineNum) override {
    assignPatternStorage[lineNum] = std::make_pair(varName, expr);
  }

  void setWhilePattern(int lineNum, const string &varName) override {
    whilePatternStorage[lineNum].insert(varName);
  }

  void setIfPattern(int lineNum, const string &varName) override {
    ifPatternStorage[lineNum].insert(varName);
  }

  void setCallsRelationship(const string &caller,
                            const string &callee) override {
    callsStorage[caller].insert(callee);
  }

  void setCFG(const string &procName, unique_ptr<CFG> cfg) override {
    cfgStorage[procName] = std::move(cfg);
  }

  void addNext(int from, int to) override {
    if (to != common::CFG_END_STMT_NUM) {
      nextStorage[from].insert(to);
    }
  }

  [[nodiscard]] bool isVariablesEqual(
      const unordered_set<string> &variables) const {
    return variableStorage == variables;
  }

  [[nodiscard]] bool isConstantsEqual(
      const unordered_set<string> &constants) const {
    return constantStorage == constants;
  }

  [[nodiscard]] bool isStmtToProcEqual(
      const unordered_map<int, string> &stmtToProcs) const {
    return stmtToProcStorage == stmtToProcs;
  }

  [[nodiscard]] bool isStmtTypeEquals(StmtType stmtType,
                                      const unordered_set<int> &stmts) const {
    auto it = statementStorage.find(stmtType);
    if (it == statementStorage.end()) {
      return stmts.empty();
    }
    return it->second == stmts;
  }

  [[nodiscard]] bool isFollowsEqual(
      const unordered_map<int, set<int>> &follows) const {
    return followsStorage == follows;
  }

  [[nodiscard]] bool isParentEqual(
      const unordered_map<int, set<int>> &parent) const {
    return parentStorage == parent;
  }

  [[nodiscard]] bool isParentStarEqual(
      const unordered_map<int, set<int>> &parentStar) const {
    return parentStarStorage == parentStar;
  }

  [[nodiscard]] bool isUsesEqual(
      unordered_map<string, unordered_set<int>> &uses) const {
    return usesStorage == uses;
  }

  [[nodiscard]] bool isUsesEqual(
      unordered_map<string, unordered_set<string>> &uses) const {
    return usesProcStorage == uses;
  }

  [[nodiscard]] bool isModifiesEqual(
      unordered_map<string, unordered_set<int>> &modifies) const {
    return modifiesStorage == modifies;
  }

  [[nodiscard]] bool isModifiesEqual(
      unordered_map<string, unordered_set<string>> &modifies) const {
    return modifiesProcStorage == modifies;
  }

  [[nodiscard]] bool isAssignPatternEqual(
      unordered_map<int, std::pair<string, string>> &assignPattern) const {
    return assignPatternStorage == assignPattern;
  }

  [[nodiscard]] bool isWhilePatternEqual(
      unordered_map<int, unordered_set<string>> &whilePattern) const {
    return whilePatternStorage == whilePattern;
  }

  [[nodiscard]] bool isIfPatternEqual(
      unordered_map<int, unordered_set<string>> &ifPattern) const {
    return ifPatternStorage == ifPattern;
  }

  [[nodiscard]] bool isCallsEqual(
      unordered_map<string, unordered_set<string>> &calls) const {
    return callsStorage == calls;
  }

  [[nodiscard]] bool isCFGEqual(
      const unordered_map<string, unique_ptr<CFG>> &other) const {
    if (cfgStorage.size() != other.size()) {
      return false;
    }

    return std::all_of(cfgStorage.begin(), cfgStorage.end(),
                       [&](const auto &pair) {
                         const string &procName = pair.first;
                         const unique_ptr<CFG> &cfgPtr = pair.second;
                         return other.find(procName) != other.end() &&
                                *cfgPtr == *other.at(procName);
                       });
  }

  [[nodiscard]] bool isNextEqual(const IntToIntSetMap &next) const {
    return nextStorage == next;
  }
};
