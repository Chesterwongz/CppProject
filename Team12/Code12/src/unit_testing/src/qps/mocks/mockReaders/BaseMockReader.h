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
#include "../MockPKBReaderData.h"

using std::vector, std::set, std::string, std::pair;

class BaseMockReader : public PKBReader {
 public:
  vector<string> mockAllVariables;
  vector<string> mockAllConstants;
  vector<string> mockAllProcedures;
  vector<string> mockStatements;
  BaseMockReader() : PKBReader(MOCK_STORE) {};

  std::vector<std::string> getAllVariables() override {
    return mockAllVariables;
  }

  std::vector<std::string> getAllConstants() override {
    return mockAllConstants;
  }

  std::vector<std::string> getAllProcedures() override {
    return mockAllProcedures;
  }

  std::vector<std::string> getAllStmtsOf(StmtType statementType) override {
    return mockStatements;
  }
};
