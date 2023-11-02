#include "SynonymRes.h"

#include <cassert>
#include <utility>

SynonymRes::SynonymRes(const string& defaultSynonymValue) {
  this->attributeMap[ATTR_REF_DEFAULT] = defaultSynonymValue;
}

SynonymRes::SynonymRes(unordered_map<AttrRef, string> attributeMap)
    : attributeMap(std::move(attributeMap)) {}

string SynonymRes::toString() const {
  assert(isAttrExists(ATTR_REF_DEFAULT));
  return this->attributeMap.at(ATTR_REF_DEFAULT);
}

string SynonymRes::getAttribute(const AttrRef& attrRef) const {
  bool isAttributeSpecified =
      this->attributeMap.find(attrRef) != this->attributeMap.end();
  if (isAttributeSpecified) {
    return attributeMap.at(attrRef);
  }
  return {};
}

bool SynonymRes::isAttrExists(const AttrRef& attrRef) const {
  return this->attributeMap.find(attrRef) != this->attributeMap.end();
}

bool SynonymRes::operator==(const SynonymRes& other) const {
  assert(this->isAttrExists(ATTR_REF_DEFAULT));
  assert(other.isAttrExists(ATTR_REF_DEFAULT));
  return this->attributeMap.at(ATTR_REF_DEFAULT) ==
         other.attributeMap.at(ATTR_REF_DEFAULT);
}

bool SynonymRes::operator!=(const SynonymRes& other) const {
  return !(*this == other);
}
