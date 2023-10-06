#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "pkb/facade/PKBWriter.h"
#include "common/cfg/CFG.h"

using std::string, std::unordered_set, std::unordered_map, std::set;

class MockPKBWriter : public PKBWriter {
 private:
  unordered_set<string> variableStorage;
  unordered_set<string> constantStorage;
  unordered_map<string, int> procedureStorage;
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

 public:
  explicit MockPKBWriter(PKBStorage &storage) : PKBWriter(storage){};
  ~MockPKBWriter() override = default;

  void setFollowsRelationship(int statementNumber,
                              int followingStatement) override {
    followsStorage[statementNumber].insert(followingStatement);
  }

  void setParentRelationship(int statementNumber, int childStatement) override {
    parentStorage[statementNumber].insert(childStatement);
  }

  void setParentStarRelationship(int statementNumber,
                                 int childStatement) override {
    parentStarStorage[statementNumber].insert(childStatement);
  }

  void setModifiesRelationship(const string &variableName,
                               int statementNumber) override {
    modifiesStorage[variableName].insert(statementNumber);
  }

  void setModifiesRelationship(const string &variableName,
                               const string &procName) override {
    modifiesProcStorage[variableName].insert(procName);
  }

  void setUsesRelationship(const string &variableName,
                           int statementNumber) override {
    usesStorage[variableName].insert(statementNumber);
  }

  void setUsesRelationship(const string &variableName,
                           const string &procName) override {
    usesProcStorage[variableName].insert(procName);
  }

  void setVariable(const string &variableName) override {
    variableStorage.insert(variableName);
  }

  void setConstant(const string &constantValue) override {
    constantStorage.insert(constantValue);
  }

  void setProcedure(const string &procedureName, int startStatement) override {
    procedureStorage[procedureName] = startStatement;
  }

  void setStatement(int statementNumber, StmtType statementType) override {
    statementStorage[statementType].insert(statementNumber);
  }

  void setAssignPattern(const string &variableName, const string &expression,
                        int lineNum) override {
    assignPatternStorage[lineNum] = std::make_pair(variableName, expression);
  }

  void setWhilePattern(int lineNum, const string &variableName) override {
    whilePatternStorage[lineNum].insert(variableName);
  }

  void setIfPattern(int lineNum, const string &variableName) override {
    ifPatternStorage[lineNum].insert(variableName);
  }

  void setCallsRelationship(const string &caller,
                            const string &callee) override {
    callsStorage[caller].insert(callee);
  }

  [[nodiscard]] bool isVariablesEqual(
      const unordered_set<string> &variables) const {
    return variableStorage == variables;
  }

  [[nodiscard]] bool isConstantsEqual(
      const unordered_set<string> &constants) const {
    return constantStorage == constants;
  }

  [[nodiscard]] bool isProceduresEqual(
      const unordered_map<string, int> &procedures) const {
    return procedureStorage == procedures;
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
};
