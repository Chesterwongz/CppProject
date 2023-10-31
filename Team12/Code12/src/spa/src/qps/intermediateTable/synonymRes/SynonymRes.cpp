#include "SynonymRes.h"

#include <cassert>
#include <utility>

SynonymRes::SynonymRes(const string& defaultSynonymValue) {
  this->attributeMap[AttrRefEnum::DEFAULT] = defaultSynonymValue;
}

SynonymRes::SynonymRes(unordered_map<AttrRefEnum, string> attributeMap)
    : attributeMap(std::move(attributeMap)) {}

string SynonymRes::toString() const {
  assert(isAttrExists(AttrRefEnum::DEFAULT));
  return this->attributeMap.at(AttrRefEnum::DEFAULT);
}

string SynonymRes::getAttribute(AttrRefEnum attrRef) const {
  bool isAttributeSpecified =
      this->attributeMap.find(attrRef) != this->attributeMap.end();
  if (isAttributeSpecified) {
    return attributeMap.at(attrRef);
  }
  return {};
}

string SynonymRes::getAttribute(const AttrRef& attrRef) const {
  return getAttribute(SynonymResUtils::attrRefToEnumMap.at(attrRef));
}

SynonymRes SynonymRes::clone() const {
  assert(isAttrExists(AttrRefEnum::DEFAULT));
  unordered_map<AttrRefEnum, string> attrRefCopy = this->attributeMap;
  return SynonymRes(attrRefCopy);
}

bool SynonymRes::isAttrExists(AttrRefEnum attrRef) const {
  return this->attributeMap.find(attrRef) != this->attributeMap.end();
}

bool SynonymRes::isAttrExists(const AttrRef& attrRef) const {
  return isAttrExists(SynonymResUtils::attrRefToEnumMap.at(attrRef));
}

bool SynonymRes::operator==(const SynonymRes& other) const {
  assert(this->isAttrExists(AttrRefEnum::DEFAULT));
  assert(other.isAttrExists(AttrRefEnum::DEFAULT));
  return this->attributeMap.at(AttrRefEnum::DEFAULT) ==
         other.attributeMap.at(AttrRefEnum::DEFAULT);
}

bool SynonymRes::operator!=(const SynonymRes& other) const {
  return !(*this == other);
}

bool SynonymRes::operator<(const SynonymRes& other) const {
  assert(this->isAttrExists(AttrRefEnum::DEFAULT));
  assert(other.isAttrExists(AttrRefEnum::DEFAULT));
  return this->attributeMap.at(AttrRefEnum::DEFAULT) <
         other.attributeMap.at(AttrRefEnum::DEFAULT);
}
