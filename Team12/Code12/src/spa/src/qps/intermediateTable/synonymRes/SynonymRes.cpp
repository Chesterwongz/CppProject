#include "SynonymRes.h"

#include <utility>

SynonymRes::SynonymRes(string  defaultSynonymValue)
    : defaultSynonymValue(std::move(defaultSynonymValue)) {}

string SynonymRes::toString() { return this->defaultSynonymValue; }

string SynonymRes::getAttribute(AttrRef attrRef) {
  if (attrRef == AttrRef::DEFAULT) {
    return this->defaultSynonymValue;
  }
  bool isAttributeSpecified =
      this->attributeMap.find(attrRef) != this->attributeMap.end();
  if (isAttributeSpecified) {
    return attributeMap.at(attrRef);
  }
  return {};
}

unique_ptr<SynonymRes> SynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return std::move(std::make_unique<SynonymRes>(synonymValueCopy));
}

bool SynonymRes::operator==(const SynonymRes& other) const {
  return this->defaultSynonymValue == other.defaultSynonymValue &&
         this->attributeMap == other.attributeMap;
}

bool SynonymRes::operator!=(const SynonymRes& other) const {
  return !(*this == other);
}
