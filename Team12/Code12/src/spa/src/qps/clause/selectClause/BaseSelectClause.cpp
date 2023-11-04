#include "BaseSelectClause.h"

#include <memory>
#include <set>

using std::unique_ptr;

void BaseSelectClause::addSynonymsInOtherClause(const set<string>& synonyms) {
  for (const auto& syn : synonyms) {
    synonymsInOtherClauses.insert(syn);
  }
}
