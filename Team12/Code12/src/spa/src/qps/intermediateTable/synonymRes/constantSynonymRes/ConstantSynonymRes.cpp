#include "ConstantSynonymRes.h"

ConstantSynonymRes::ConstantSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::VALUE_ENUM] = defaultSynonymValue;
}

unique_ptr<SynonymRes> ConstantSynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return std::move(std::make_unique<ConstantSynonymRes>(synonymValueCopy));
}
