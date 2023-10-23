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
#include "pkb/storage/NextStore.h"

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

  vector<string> getPrevStmts(int secondStmtNumber,
                              StmtType firstStmtType) override {
    return mockGetPrevStmts;
  };

  vector<string> getNextStmts(int firstStmtNumber,
                              StmtType secondStmtType) override {
    return mockGetNextStmts;
  }

  vector<pair<string, string>> getNextTPairs(StmtType firstStmtType,
                                             StmtType secondStmtType) override {
    return mockGetNextTPairs;
  }

  bool isNextT(int firstStmtNumber, int secondStmtNumber) override {
    return mockIsNextT;
  }

  vector<string> getPrevTStmts(int secondStmtNumber,
                               StmtType firstStmtType) override {
    return mockGetPrevTStmts;
  }

  vector<string> getNextTStmts(int firstStmtNumber,
                               StmtType secondStmtType) override {
    return mockGetNextTStmts;
  }
};
