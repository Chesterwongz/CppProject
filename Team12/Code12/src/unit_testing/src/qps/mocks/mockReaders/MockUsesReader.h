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
#include "pkb/storage/UsesPStore.h"
#include "pkb/storage/UsesSStore.h"

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

  explicit MockUsesReader() : BaseMockReader() {}

  vector<string> getStatementsUsing(const string& variableName,
                                    StmtType statementType) override {
    return mockStatementsUsing;
  }

  vector<string> getProcUsing(const std::string& variableName) override {
    return mockProcUsing;
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
