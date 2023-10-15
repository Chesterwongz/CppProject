#include "SynonymRes.h"

#include <utility>

SynonymRes::SynonymRes(string defaultSynonymValue)
    : defaultSynonymValue(std::move(defaultSynonymValue)) {}

SynonymRes::SynonymRes(string defaultSynonymValue,
                       unordered_map<AttrRef, string> attributeMap)
    : defaultSynonymValue(std::move(defaultSynonymValue)),
      attributeMap(std::move(attributeMap)) {}

string SynonymRes::toString() const { return this->defaultSynonymValue; }

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

SynonymRes SynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  unordered_map<AttrRef, string> attrRefCopy = this->attributeMap;
  return SynonymRes(synonymValueCopy, attrRefCopy);
}

bool SynonymRes::operator==(const SynonymRes& other) const {
  return this->defaultSynonymValue == other.defaultSynonymValue &&
         this->attributeMap == other.attributeMap;
}

bool SynonymRes::operator!=(const SynonymRes& other) const {
  return !(*this == other);
}

SynonymRes SynonymRes::buildDefaultSynonym(const string& value) {
  return SynonymRes(value);
  ;
}

SynonymRes SynonymRes::buildCallsSynonym(const string& stmtNumber,
                                         string procName) {
  SynonymRes synonymRes = SynonymRes(stmtNumber);
  synonymRes.attributeMap[AttrRef::STMT_NUM_ENUM] = stmtNumber;
  synonymRes.attributeMap[AttrRef::PROC_NAME_ENUM] = std::move(procName);
  return synonymRes;
}

SynonymRes SynonymRes::buildConstantSynonym(const string& value) {
  SynonymRes synonymRes = SynonymRes(value);
  synonymRes.attributeMap[AttrRef::VALUE_ENUM] = value;
  return synonymRes;
}

SynonymRes SynonymRes::buildProcSynonym(const string& procName) {
  SynonymRes synonymRes = SynonymRes(procName);
  synonymRes.attributeMap[AttrRef::PROC_NAME_ENUM] = procName;
  return synonymRes;
}

SynonymRes SynonymRes::buildStmtSynonym(const string& stmtNumber) {
  SynonymRes synonymRes = SynonymRes(stmtNumber);
  synonymRes.attributeMap[AttrRef::STMT_NUM_ENUM] = stmtNumber;
  return synonymRes;
}

SynonymRes SynonymRes::buildVarSynonym(const string& varName) {
  SynonymRes synonymRes = SynonymRes(varName);
  synonymRes.attributeMap[AttrRef::VAR_NAME_ENUM] = varName;
  return synonymRes;
}
