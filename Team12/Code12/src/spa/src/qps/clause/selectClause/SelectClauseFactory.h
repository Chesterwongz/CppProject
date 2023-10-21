#pragma once

#include <memory>

#include "qps/clause/selectClause/selectBooleanClause/SelectBooleanClause.h"
#include "qps/clause/selectClause/selectTupleClause/SelectTupleClause.h"

using std::unique_ptr;

class SelectClauseFactory {
 public:
  static unique_ptr<ISelectClause> buildSelectClause(
      SynonymsToSelect synonymsToSelect);
};
