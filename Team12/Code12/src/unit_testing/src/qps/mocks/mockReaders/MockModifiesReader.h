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
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesSStore.h"

using std::vector, std::set, std::string, std::pair;

class MockModifiesReader : public BaseMockReader {
 public:
  vector<string> mockStatementsModifying;
  vector<string> mockProceduresModifying;
  vector<string> mockVariablesModifiedBy;
  vector<string> mockVarsModifiedByProc;
  vector<pair<string, string>> mockAllModifiedVariables;
  vector<pair<string, string>> mockModifiesProcPairs;
  bool mockIsVariableModifiedBy {};
  bool mockIsVariableModifiedByProc {};

  MockModifiesReader() : BaseMockReader() {}

  vector<string> getStatementsModifying(const string& variableName,
                                        StmtType statementType) override {
    return mockStatementsModifying;
  }

  vector<string> getProcModifying(const std::string& varName) override {
    return mockProceduresModifying;
  }

  vector<string> getVariablesModifiedBy(int statementNumber) override {
    return mockVariablesModifiedBy;
  }

  // return all variables modified by specified procedure
  vector<string> getVarsModifiedByProc(const string& procName) override {
    return mockVarsModifiedByProc;
  }

  vector<pair<string, string>> getModifiesStmtPairs(
      StmtType statementType) override {
    return mockAllModifiedVariables;
  }

  vector<pair<string, string>> getModifiesProcPairs() override {
    return mockModifiesProcPairs;
  }

  bool isVariableModifiedBy(int stmtNum, const string& variableName) override {
    return mockIsVariableModifiedBy;
  }

  bool isVariableModifiedByProc(const string& procName,
                                const string& varName) override {
    return mockIsVariableModifiedByProc;
  }
};
