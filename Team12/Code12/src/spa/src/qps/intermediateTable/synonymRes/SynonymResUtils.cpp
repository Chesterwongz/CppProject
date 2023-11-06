#include "SynonymResUtils.h"

string SynonymResUtils::buildKey(unordered_map<AttrRef, string> attributeMap) {
  string key;
  for (const AttrRef& attrRef : SynonymResUtils::ALL_ATTR_REF) {
    bool isAttrExists = attributeMap.find(attrRef) != attributeMap.end();
    key += (isAttrExists ? attributeMap.at(attrRef) : EMPTY_STRING) + DELIMITER;
  }
  return key;
}
