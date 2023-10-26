#pragma once

#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/clause/selectClause/SelectClauseFactory.h"

using std::vector, std::unique_ptr, std::string;

typedef vector<unique_ptr<Clause>> ClauseList;

class Query {
 private:
  unique_ptr<BaseSelectClause> selectClause = {};
  ClauseList clauses = {};


 public:
  void addClause(unique_ptr<Clause> clause);

  void setSynonymToQuery(SynonymsToSelect selectSynonyms);

  IntermediateTable evalSelectClause(PKBReader& pkb);

  bool operator==(const Query& other);

  friend class QueryEvaluator;
};
