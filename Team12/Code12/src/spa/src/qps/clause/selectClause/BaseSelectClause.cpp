#include "BaseSelectClause.h"

#include <memory>
#include <set>

#include "qps/clause/utils/ClauseUtil.h"

using std::unique_ptr;

bool BaseSelectClause::isDisableCaching() { return true; }

void BaseSelectClause::addSynonymsInOtherClause(const set<string>& synonyms) {
  for (const auto& syn : synonyms) {
    synonymsInOtherClauses.insert(syn);
  }
}
ClauseKey BaseSelectClause::getKey() {
  ClauseKey key = SELECT_KEYWORD + ClauseUtil::KEY_DELIMITER;
  for (const unique_ptr<SynonymArg>& syn : synonymsToSelect) {
    key += syn->getArgKey() + ClauseUtil::KEY_DELIMITER;
  }
  return key;
}
