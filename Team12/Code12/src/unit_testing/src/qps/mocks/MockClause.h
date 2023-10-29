#pragma once

#include <set>
#include <string>
#include <vector>

#include "qps/clause/Clause.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::set, std::vector;

class MockClause : public Clause {
  IntermediateTable mockEvaluate =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  bool mockIsEquals = false;
  set<string> mockClauseSynonyms = {};

 public:
  explicit MockClause(vector<string> synonyms) {
    set<string> synonymSet(synonyms.begin(), synonyms.end());
    mockClauseSynonyms = synonymSet;
  }

  IntermediateTable evaluate(PKBReader& pkb) override {
      return mockEvaluate;
  }

  bool isEquals(const Clause& other) override {
      return mockIsEquals;
  }

  set<string> getClauseSynonyms() override {
      return mockClauseSynonyms;
  }
};
