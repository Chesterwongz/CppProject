#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "BaseMockReader.h"
#include "pkb/facade/PKBReader.h"

using std::vector, std::set, std::string, std::pair;

class MockUsesReader : public BaseMockReader {
 public:
  vector<string> mockStatementsUsing;
  vector<string> mockProcUsing;
  vector<string> mockVariablesUsedBy;
  vector<string> mockVarUsedByProc;
  vector<pair<string, string>> mockAllUsedVariables;
  vector<pair<string, string>> mockUsesProcPairs;
  bool mockIsVariableUsedBy {};
  bool mockIsVariableUsedByProc {};

  MockUsesReader() : BaseMockReader() {}

  vector<string> getStatementsUsing(const string& variableName,
                                    StmtType statementType) override {
    if (variableName == common::WILDCARD_VAR) {
      vector<string> res;
      res.reserve(mockAllUsedVariables.size());
      for (auto& pair : mockAllUsedVariables) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockStatementsUsing;
    }
  }

  vector<string> getProcUsing(const std::string& variableName) override {
    if (variableName == common::WILDCARD_VAR) {
      vector<string> res;
      res.reserve(mockUsesProcPairs.size());
      for (auto& pair : mockUsesProcPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockProcUsing;
    }
  }

  std::vector<std::string> getVariablesUsedBy(int statementNumber) override {
    return mockVariablesUsedBy;
  }

  vector<string> getVarsUsedByProc(const std::string& procName) override {
    return mockVarUsedByProc;
  }

  vector<pair<string, string>> getUsesStmtPairs(
      StmtType statementType) override {
    return mockAllUsedVariables;
  }

  vector<pair<string, string>> getUsesProcPairs() override {
    return mockUsesProcPairs;
  }

  bool isVariableUsedBy(int stmt, const string& varName) override {
    return mockIsVariableUsedBy;
  }

  bool isVariableUsedByProc(const string& variableName,
                            const string& procName) override {
    return mockIsVariableUsedByProc;
  }
};
