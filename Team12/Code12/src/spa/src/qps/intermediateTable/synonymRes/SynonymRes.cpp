#include "SynonymRes.h"

#include <utility>

SynonymRes::SynonymRes(string defaultSynonymValue)
    : defaultSynonymValue(std::move(defaultSynonymValue)) {}

SynonymRes::SynonymRes(string defaultSynonymValue,
                       unordered_map<AttrRefEnum, string> attributeMap)
    : defaultSynonymValue(std::move(defaultSynonymValue)),
      attributeMap(std::move(attributeMap)) {}

string SynonymRes::toString() const { return this->defaultSynonymValue; }

string SynonymRes::getAttribute(AttrRefEnum attrRef) {
  if (attrRef == AttrRefEnum::DEFAULT) {
    return this->defaultSynonymValue;
  }
  bool isAttributeSpecified =
      this->attributeMap.find(attrRef) != this->attributeMap.end();
  if (isAttributeSpecified) {
    return attributeMap.at(attrRef);
  }
  return {};
}

SynonymRes SynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  unordered_map<AttrRefEnum, string> attrRefCopy = this->attributeMap;
  return SynonymRes(synonymValueCopy, attrRefCopy);
}

bool SynonymRes::isAttrExists(AttrRefEnum attrRef) const {
  return this->attributeMap.find(attrRef) != this->attributeMap.end();
}

bool SynonymRes::operator==(const SynonymRes& other) const {
  return this->defaultSynonymValue == other.defaultSynonymValue;
}

bool SynonymRes::operator!=(const SynonymRes& other) const {
  return !(*this == other);
}
