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

  vector<string> getAffects(int s1, StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockAffectsPairs.size());
      for (auto &pair : mockAffectsPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockAffects;
    }
  }

  vector<string> getAffectedBy(int s2, StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockAffectsPairs.size());
      for (auto &pair : mockAffectsPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockAffectedBy;
    }
  }

  vector<pair<string, string>> getAffectsPairs() override {
    return mockAffectsPairs;
  }

  bool isAffects(int statementNumber, int followingStatement) override {
    return mockIsAffects;
  }

  bool hasAffects() override { return !mockAffectsPairs.empty(); }
};
