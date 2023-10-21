#include "SelectClauseFactory.h"

unique_ptr<ISelectClause> SelectClauseFactory::buildSelectClause(
    SynonymsToSelect synonymsToSelect) {
  if (synonymsToSelect.empty()) {
    return std::make_unique<SelectBooleanClause>(std::move(synonymsToSelect));
  } else {
    return std::make_unique<SelectTupleClause>(std::move(synonymsToSelect));
  }
}
