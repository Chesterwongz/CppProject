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

  explicit MockCallsReader() : BaseMockReader() {}

  std::vector<std::string> getCallerProcs(const std::string& proc2) override {
    return mockCallerProcs;
  }

  std::vector<std::string> getCallerProcsStar(
      const std::string& proc2) override {
    return mockCallerProcsStar;
  }

  std::vector<std::string> getCalleeProcs(const std::string& proc1) override {
    return mockCalleeProcs;
  }

  std::vector<std::string> getCalleeProcsStar(
      const std::string& proc1) override {
    return mockCalleeProcsStar;
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
};
