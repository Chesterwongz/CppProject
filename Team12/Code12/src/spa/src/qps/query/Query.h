#pragma once

#include <algorithm>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/clause/selectClause/SelectClauseFactory.h"
#include "qps/clause/utils/ClauseUtil.h"

using std::vector, std::unique_ptr, std::string, std::set, std::unordered_set;

class Query {
 private:
  unique_ptr<BaseSelectClause> selectClause = {};
  ClauseUtil::ClauseList clauses = {};
  ClauseUtil::NotClauseList notClauses = {};

 public:
  void addNotClause(unique_ptr<NotDecorator> notClause);

  void addClause(unique_ptr<Clause> clause);

  void setSynonymToQuery(SynonymsToSelect selectSynonyms);

  IntermediateTable evalSelectClause(PKBReader& pkb);

  set<string> getSelectedSynonyms();

  unordered_set<string> getQueryResult(IntermediateTable& finalTable);

  bool operator==(const Query& other);

  friend class QueryEvaluator;
};
