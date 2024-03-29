#include "SelectClauseFactory.h"

unique_ptr<BaseSelectClause> SelectClauseFactory::createSelectClause(
    SynonymsToSelect synonymsToSelect) {
  if (synonymsToSelect.empty()) {
    return std::make_unique<SelectBooleanClause>(std::move(synonymsToSelect));
  } else {
    return std::make_unique<SelectTupleClause>(std::move(synonymsToSelect));
  }
}
