#include "SynonymRes.h"

SynonymRes::SynonymRes(const string& defaultSynonymValue)
    : defaultSynonymValue(defaultSynonymValue) {}

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

bool SynonymRes::operator==(const SynonymRes& other) {
  return this->defaultSynonymValue == other.defaultSynonymValue &&
         this->attributeMap == other.attributeMap;
}
