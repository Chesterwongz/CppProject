#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../intermediateTable/IntermediateTableFactory.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/Clause.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/clause/selectClause/SelectClauseFactory.h"
#include "qps/clause/selectClause/selectTupleClause/SelectTupleClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/query/Query.h"

using std::set, std::vector, std::unique_ptr, std::string, std::unordered_set;

typedef vector<unique_ptr<Clause>> ClauseList;

class QueryEvaluator {
 private:
  PKBReader& pkb;

 public:
  explicit QueryEvaluator(PKBReader& pkb);
  unordered_set<string> evaluate(unique_ptr<Query>& query);
};
