#include "varSynonymRes.h"

VarSynonymRes::VarSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::VAR_NAME_ENUM] = defaultSynonymValue;
}
