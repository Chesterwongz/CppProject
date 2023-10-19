#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "MockModifiesReader.h"
#include "pkb/facade/PKBReader.h"

using std::vector, std::set, std::string, std::pair;

class MockPatternsReader : public MockModifiesReader {
 public:
  vector<pair<string, string>> mockExactAssignPattern;
  vector<pair<string, string>> mockPartialAssignPattern;
  vector<pair<string, string>> mockIfPattern;
  vector<pair<string, string>> mockWhilePattern;

  explicit MockPatternsReader() : MockModifiesReader() {}

  vector<pair<string, string>> getExactAssignPattern(
      const string& variableName, const string& rpn) override {
    return mockExactAssignPattern;
  }

  vector<pair<string, string>> getPartialAssignPattern(
      const string& variableName, const string& rpn) override {
    return mockPartialAssignPattern;
  }

  vector<pair<string, string>> getIfPattern(
      const string& variableName) override {
    return mockIfPattern;
  }

  vector<pair<string, string>> getWhilePattern(
      const string& variableName) override {
    return mockWhilePattern;
  }

  void resetMockExactAssignPatternStmts() { this->mockExactAssignPattern = {}; }

  void resetMockPartialAssignPatternStmts() {
    this->mockPartialAssignPattern = {};
  }
};
