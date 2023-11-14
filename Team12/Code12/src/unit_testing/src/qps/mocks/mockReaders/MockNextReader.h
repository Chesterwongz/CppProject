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
#include "pkb/facade/PKBStore.h"
#include "pkb/storage/relation_storage/NextStore.h"

using std::vector, std::set, std::string, std::pair;

class MockNextReader : public BaseMockReader {
 public:
  vector<pair<string, string>> mockGetNextPairs;
  bool mockIsNext {};
  vector<string> mockGetPrevStmts;
  vector<string> mockGetNextStmts;
  vector<pair<string, string>> mockGetNextTPairs;
  bool mockIsNextT {};
  vector<string> mockGetPrevTStmts;
  vector<string> mockGetNextTStmts;

  MockNextReader() : BaseMockReader() {}

  vector<pair<string, string>> getNextPairs(StmtType firstStmtType,
                                            StmtType secondStmtType) override {
    return mockGetNextPairs;
  }

  bool isNext(int firstStmtNumber, int secondStmtNumber) override {
    return mockIsNext;
  }

  vector<string> getPrevStmts(int s2, StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockGetNextPairs.size());
      for (auto &pair : mockGetNextPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockGetPrevStmts;
    }
  };

  vector<string> getNextStmts(int s1, StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockGetNextPairs.size());
      for (auto &pair : mockGetNextPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockGetNextStmts;
    }
  }

  vector<pair<string, string>> getNextTPairs(StmtType firstStmtType,
                                             StmtType secondStmtType) override {
    return mockGetNextTPairs;
  }

  bool isNextT(int firstStmtNumber, int secondStmtNumber) override {
    return mockIsNextT;
  }

  vector<string> getPrevTStmts(int s2, StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockGetNextTPairs.size());
      for (auto &pair : mockGetNextTPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockGetPrevTStmts;
    }
  }

  vector<string> getNextTStmts(int s1, StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockGetNextTPairs.size());
      for (auto &pair : mockGetNextTPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockGetNextTStmts;
    }
  }

  bool hasNext() override { return !mockGetNextPairs.empty(); }

  bool hasNextT() override { return !mockGetNextTPairs.empty(); }
};
