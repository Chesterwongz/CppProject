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

class MockCallsReader : public BaseMockReader {
 public:
  vector<std::string> mockCallerProcs {};
  vector<string> mockCallerProcsStar {};
  vector<string> mockCalleeProcs {};
  vector<string> mockCalleeProcsStar {};
  vector<pair<string, string>> mockCallPairs {};
  vector<pair<string, string>> mockCallsStarPairs {};
  bool mockHasCalls {};
  bool mockHasCallsT {};

  MockCallsReader() : BaseMockReader() {}

  std::vector<std::string> getCallerProcs(const std::string& proc2) override {
    if (proc2 == common::WILDCARD_PROC) {
      std::vector<std::string> res;
      res.reserve(mockCallPairs.size());
      for (auto& pair : mockCallPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockCallerProcs;
    }
  }

  std::vector<std::string> getCallerProcsStar(
      const std::string& proc2) override {
    if (proc2 == common::WILDCARD_PROC) {
      std::vector<std::string> res;
      res.reserve(mockCallsStarPairs.size());
      for (auto& pair : mockCallsStarPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockCallerProcsStar;
    }
  }

  std::vector<std::string> getCalleeProcs(const std::string& proc1) override {
    if (proc1 == common::WILDCARD_PROC) {
      std::vector<std::string> res;
      res.reserve(mockCallPairs.size());
      for (auto& pair : mockCallPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockCalleeProcs;
    }
  }

  std::vector<std::string> getCalleeProcsStar(
      const std::string& proc1) override {
    if (proc1 == common::WILDCARD_PROC) {
      std::vector<std::string> res;
      res.reserve(mockCallsStarPairs.size());
      for (auto& pair : mockCallsStarPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockCalleeProcsStar;
    }
  }

  std::vector<std::pair<std::string, std::string>> getCallPairs() override {
    return mockCallPairs;
  }

  std::vector<std::pair<std::string, std::string>> getCallsStarPairs()
      override {
    return mockCallsStarPairs;
  }

  bool hasCalls(const std::string& proc1, const std::string& proc2) override {
    return mockHasCalls;
  }

  bool hasCallsT(const std::string& proc1, const std::string& proc2) override {
    return mockHasCallsT;
  }

  bool hasCalls() override { return !mockCallPairs.empty(); }

  bool hasCallsT() override { return !mockCallsStarPairs.empty(); }
};
