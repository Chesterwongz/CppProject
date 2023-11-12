#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/clauseCache/ClauseCache.h"
#include "qps/intermediateTable/IntermediateTable.h"

class BaseClause {
 protected:
  virtual IntermediateTable evaluate(PKBReader& pkbReader) = 0;
  friend class NotDecorator;

 public:
  IntermediateTable evaluate(PKBReader& pkb, ClauseCache& cache);
  virtual bool isEquals(const BaseClause& other) = 0;
  virtual set<string> getClauseSynonyms() = 0;
  virtual ClauseKey getKey() = 0;
  virtual ~BaseClause() = default;
};
