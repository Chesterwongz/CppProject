#pragma once

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/clause/Clause.h"

using std::set, std::vector, std::unique_ptr, std::string;

typedef vector<unique_ptr<Clause>> ClauseList;

class Query {
 private:
  PKBReader& pkb;
  unique_ptr<Context> context;
  ClauseList clauses = {};
  vector<string> synonymsToQuery = {};

 public:
  explicit Query(PKBReader& pkb);
  void addContext(unique_ptr<Context> contextToAdd);
  void addClause(unique_ptr<Clause> clause);
  void setSynonymToQuery(const string& selectSynonym);
  void setSynonymToQuery(vector<string>& selectSynonyms);

  set<string> evaluate();
  bool operator==(const Query& other);
};
