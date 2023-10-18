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
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/selectClause/SelectClause.h"

using std::set, std::vector, std::unique_ptr, std::string;

typedef vector<unique_ptr<Clause>> ClauseList;

class Query {
 private:
  PKBReader& pkb;
  vector<string> synonymsToQuery = {};
  unique_ptr<SelectClause> selectClause = {};
  ClauseList clauses = {};

 public:
  explicit Query(PKBReader& pkb);
  void addClause(unique_ptr<Clause> clause);
  void setSynonymToQuery(SynonymsToSelect selectSynonyms);

  set<string> evaluate();
  bool operator==(const Query& other);
};
