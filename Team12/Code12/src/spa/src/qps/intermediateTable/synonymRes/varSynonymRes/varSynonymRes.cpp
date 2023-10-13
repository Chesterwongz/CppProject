#include "varSynonymRes.h"

VarSynonymRes::VarSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::VAR_NAME_ENUM] = defaultSynonymValue;
}

SynonymRes VarSynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return VarSynonymRes(synonymValueCopy);
}
