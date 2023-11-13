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
    if (variableName == common::WILDCARD_VAR) {
      vector<string> res;
      res.reserve(mockAllModifiedVariables.size());
      for (auto& pair : mockAllModifiedVariables) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockStatementsModifying;
    }
  }

  vector<string> getProcModifying(const std::string& varName) override {
    if (varName == common::WILDCARD_VAR) {
      vector<string> res;
      res.reserve(mockModifiesProcPairs.size());
      for (auto& pair : mockModifiesProcPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockProceduresModifying;
    }
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
