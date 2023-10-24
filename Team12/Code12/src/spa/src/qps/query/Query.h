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
#include "qps/clause/selectClause/BaseSelectClause.h"

using std::set, std::vector, std::unique_ptr, std::string, std::unordered_set;

typedef vector<unique_ptr<Clause>> ClauseList;

class Query {
 private:
  PKBReader& pkb;
  unique_ptr<BaseSelectClause> selectClause = {};
  ClauseList clauses = {};

 public:
  explicit Query(PKBReader& pkb);
  void addClause(unique_ptr<Clause> clause);
  void setSynonymToQuery(SynonymsToSelect selectSynonyms);

  unordered_set<string> evaluate();
  bool operator==(const Query& other);
};
