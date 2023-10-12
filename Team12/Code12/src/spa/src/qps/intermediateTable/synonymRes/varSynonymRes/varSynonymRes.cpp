#include "varSynonymRes.h"

VarSynonymRes::VarSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::VAR_NAME_ENUM] = defaultSynonymValue;
}

unique_ptr<SynonymRes> SynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return std::move(std::make_unique<VarSynonymRes>(synonymValueCopy));
}
