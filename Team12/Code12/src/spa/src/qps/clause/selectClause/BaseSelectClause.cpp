#include "BaseSelectClause.h"

#include <memory>
#include <set>

using std::unique_ptr;

void BaseSelectClause::addSynonymsInOtherClause(const set<string>& synonyms) {
  for (const auto& syn : synonyms) {
    synonymsInOtherClauses.insert(syn);
  }
}
string BaseSelectClause::getKey() {
  string key = SELECT_KEYWORD + '|';
  for (const unique_ptr<SynonymArg>& syn : synonymsToSelect) {
    key += syn->getValue() + '|';
  }
  return key;
}
