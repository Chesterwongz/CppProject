#pragma once

#include <string>
#include <utility>
#include <vector>

#include "BaseMockReader.h"

using std::vector, std::string, std::pair;

class MockAffectsReader : public BaseMockReader {
 public:
  vector<string> mockAffects;
  vector<string> mockAffectedBy;
  vector<pair<string, string>> mockAffectsPairs;
  bool mockIsAffects {};

  MockAffectsReader() : BaseMockReader() {}

  vector<string> getAffects(int statementNumber,
                            StmtType statementType) override {
    return mockAffects;
  }

  vector<string> getAffectedBy(int statementNumber,
                               StmtType statementType) override {
    return mockAffectedBy;
  }

  vector<pair<string, string>> getAffectsPairs() override {
    return mockAffectsPairs;
  }

  bool isAffects(int statementNumber, int followingStatement) override {
    return mockIsAffects;
  }

  bool hasAffects() override { return !mockAffectsPairs.empty(); }
};
