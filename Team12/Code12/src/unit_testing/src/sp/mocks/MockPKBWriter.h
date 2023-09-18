#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "pkb/facade/PKBWriter.h"

class MockPKBWriter : public PKBWriter {
public:
    std::unordered_set<std::string> variableStorage;
    std::unordered_set<std::string> constantStorage;
    std::unordered_map<std::string, int> procedureStorage;
    std::unordered_map<StmtType, std::unordered_set<int>> statementStorage;
    std::unordered_map<int, std::set<int>> followsStorage;
    std::unordered_map<int, std::set<int>> parentStorage;
    std::unordered_map<std::string, std::unordered_set<int>> modifiesStorage;
    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesProcStorage; // var to proc
    std::unordered_map<std::string, std::unordered_set<int>> usesStorage;
    std::unordered_map<std::string, std::unordered_set<std::string>> usesProcStorage; // var to proc
    std::unordered_map<int, std::pair<std::string, std::string>> assignPatternStorage;
    std::unordered_map<int, std::unordered_set<std::string>> whilePatternStorage;
    std::unordered_map<int, std::unordered_set<std::string>> ifPatternStorage;
    std::unordered_map<std::string, std::unordered_set<std::string>> callsStorage;

    explicit MockPKBWriter(Storage &storage) : PKBWriter(storage){};
    ~MockPKBWriter() override = default;

    void setFollowsRelationship(int statementNumber, int followingStatement) override {
        followsStorage[statementNumber].insert(followingStatement);
    }

    void setParentRelationship(int statementNumber, int childStatement) override {
        parentStorage[statementNumber].insert(childStatement);
    }

    void setModifiesRelationship(const std::string &variableName, int statementNumber) override {
        modifiesStorage[variableName].insert(statementNumber);
    }

    void setModifiesRelationship(const std::string &variableName, const std::string& procName) override {
        modifiesProcStorage[variableName].insert(procName);
    }

    void setUsesRelationship(const std::string &variableName, int statementNumber) override {
        usesStorage[variableName].insert(statementNumber);
    }

    void setUsesRelationship(const std::string &variableName, const std::string& procName) override {
        usesProcStorage[variableName].insert(procName);
    }

    void setVariable(const std::string &variableName) override {
        variableStorage.insert(variableName);
    }

    void setConstant(const std::string &constantValue) override {
        constantStorage.insert(constantValue);
    }

    void setProcedure(const std::string &procedureName, int startStatement) override {
        procedureStorage[procedureName] = startStatement;
    }

    void setStatement(int statementNumber, StmtType statementType) override {
        statementStorage[statementType].insert(statementNumber);
    }

    void setAssignPattern(int lineNum, const std::string &variableName, const std::string &expression) override {
        assignPatternStorage[lineNum] = std::make_pair(variableName, expression);
    }

    void setWhilePattern(int lineNum, const std::string &variableName) override {
        whilePatternStorage[lineNum].insert(variableName);
    }

    void setIfPattern(int lineNum, const std::string &variableName) override {
        ifPatternStorage[lineNum].insert(variableName);
    }

    void setCallsRelationship(const std::string &caller, const std::string &callee) override {
        callsStorage[caller].insert(callee);
    }

    [[nodiscard]] bool isVariablesEqual(const std::unordered_set<std::string> &variables) const {
        return variableStorage == variables;
    }

    [[nodiscard]] bool isConstantsEqual(const std::unordered_set<std::string> &constants) const {
        return constantStorage == constants;
    }

    [[nodiscard]] bool isProceduresEqual(const std::unordered_map<std::string, int> &procedures) const {
        return procedureStorage == procedures;
    }

    [[nodiscard]] bool isStmtTypeEquals(StmtType stmtType, const std::unordered_set<int> &stmts) const {
        auto it = statementStorage.find(stmtType);
        if (it == statementStorage.end()) {
            return stmts.empty();
        }
        return it->second == stmts;
    }

    [[nodiscard]] bool isFollowsEqual(const std::unordered_map<int, std::set<int>> &follows) const {
        return followsStorage == follows;
    }

    [[nodiscard]] bool isParentEqual(const std::unordered_map<int, std::set<int>> &parent) const {
        return parentStorage == parent;
    }

    [[nodiscard]] bool isUsesEqual(std::unordered_map<std::string, std::unordered_set<int>> &uses) const {
        return usesStorage == uses;
    }

    [[nodiscard]] bool isUsesEqual(std::unordered_map<std::string, std::unordered_set<string>> &uses) const {
        return usesProcStorage == uses;
    }

    [[nodiscard]] bool isModifiesEqual(std::unordered_map<std::string, std::unordered_set<int>> &modifies) const {
        return modifiesStorage == modifies;
    }

    [[nodiscard]] bool isModifiesEqual(std::unordered_map<std::string, std::unordered_set<string>> &modifies) const {
        return modifiesProcStorage == modifies;
    }

    [[nodiscard]] bool isAssignPatternEqual(std::unordered_map<int, std::pair<std::string, std::string>> &assignPattern) const {
        return assignPatternStorage == assignPattern;
    }

    [[nodiscard]] bool isWhilePatternEqual(std::unordered_map<int, std::unordered_set<std::string>> &whilePattern) const {
        return whilePatternStorage == whilePattern;
    }

    [[nodiscard]] bool isIfPatternEqual(std::unordered_map<int, std::unordered_set<std::string>> &ifPattern) const {
        return ifPatternStorage == ifPattern;
    }

    [[nodiscard]] bool isCallsEqual(std::unordered_map<std::string, std::unordered_set<std::string>> &calls) const {
        return callsStorage == calls;
    }
};
